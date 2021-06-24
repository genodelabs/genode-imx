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

#ifndef _LX_KIT__MEMORY_H_
#define _LX_KIT__MEMORY_H_

#include <base/allocator_avl.h>
#include <base/cache.h>
#include <base/env.h>
#include <base/heap.h>
#include <base/registry.h>

namespace Platform { class Connection; };
namespace Lx_kit {
	using namespace Genode;
	class Mem_allocator;
}


class Lx_kit::Mem_allocator
{
	public:

		Mem_allocator(Env                  & env,
		              Heap                 & heap,
		              Platform::Connection & platform,
		              Cache                  cache_attr);

		void * alloc(size_t size, size_t align);
		void * dma_addr(void * addr);
		size_t size(const void * ptr);
		bool   free(const void * ptr);

	private:

		struct Buffer
		{
			size_t                   size;
			Ram_dataspace_capability cap;
			addr_t                   addr;

			Buffer(size_t size, Ram_dataspace_capability cap, addr_t addr)
			: size(size), cap(cap), addr(addr) {}
		};

		using Buffer_element  = Registered_no_delete<Buffer>;
		using Buffer_registry = Registry<Buffer_element>;

		Env                  & _env;
		Heap                 & _heap;
		Platform::Connection & _platform;
		Cache                  _cache_attr;
		Allocator_avl          _mem;
		Buffer_registry        _buffers {};
};

#endif /* _LX_KIT__MEMORY_H_ */
