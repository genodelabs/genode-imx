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

		class Buffer : public Attached_dataspace
		{
			private:

				addr_t const _dma_addr;

			public:

				Buffer(Region_map         & rm,
				       Dataspace_capability cap,
				       addr_t               dma_addr)
				: Attached_dataspace(rm, cap), _dma_addr(dma_addr) {}

				addr_t dma_addr() const {
					return _dma_addr; }
		};

		Mem_allocator(Env                  & env,
		              Heap                 & heap,
		              Platform::Connection & platform,
		              Cache                  cache_attr);

		Buffer & alloc_buffer(size_t size);
		void *   alloc(size_t size, size_t align);
		addr_t   dma_addr(void * addr);
		size_t   size(const void * ptr);
		void     free(Buffer & buffer);
		bool     free(const void * ptr);

	private:

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
