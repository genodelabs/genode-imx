/**
 * \brief  Lx_kit memory allocation backend
 * \author Stefan Kalkowski
 * \date   2021-03-25
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

/* Genode includes */
#include <base/log.h>
#include <os/backtrace.h>
#include <platform_session/connection.h>

/* local includes */
#include <lx_kit/memory.h>


Lx_kit::Mem_allocator::Mem_allocator(Genode::Env          & env,
                                     Heap                 & heap,
                                     Platform::Connection & platform,
                                     Cache                  cache_attr)
:
	_env(env), _heap(heap), _platform(platform),
	_cache_attr(cache_attr), _mem(&heap) {}


void * Lx_kit::Mem_allocator::alloc(size_t size, size_t align)
{
	if (!size)
		return nullptr;

	void * out_addr = nullptr;

	if (_mem.alloc_aligned(size, &out_addr, log2(align)).error()) {

		/* allocation failed, so we request a new DMA-capable dataspace */
		size_t ds_size = align_addr(size, 12);
		Ram_dataspace_capability ds_cap =
			_platform.alloc_dma_buffer(ds_size, _cache_attr);

		try {
			addr_t addr = (addr_t) _env.rm().attach(ds_cap);
			_mem.add_range(addr, ds_size);
			new (_heap) Buffer_element(_buffers, ds_size, ds_cap, addr);
		} catch (Out_of_caps) {
			_platform.free_dma_buffer(ds_cap);
			throw;
		}

		/* re-try allocation */
		_mem.alloc_aligned(size, &out_addr, log2(align));
	}

	if (!out_addr) {
		error("memory allocation failed for ", size, " align ", align);
		backtrace();
	}
	else
		memset(out_addr, 0, size);

	return out_addr;
}


void * Lx_kit::Mem_allocator::dma_addr(void * addr)
{
	void * ret = nullptr;

	_buffers.for_each([&] (Buffer & b) {
		if (b.addr > (addr_t)addr || (b.addr+b.size) <= (addr_t)addr)
			return;

		ret = (void*)_platform.dma_addr(b.cap);
	});

	return ret;
}


bool Lx_kit::Mem_allocator::free(const void * ptr)
{
	if (!_mem.valid_addr((addr_t)ptr))
		return false;

	_mem.free(const_cast<void*>(ptr));
	return true;
}


Genode::size_t Lx_kit::Mem_allocator::size(const void * ptr)
{
	return ptr ? _mem.size_at(ptr) : 0;
}
