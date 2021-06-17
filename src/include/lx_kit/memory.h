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

#include <base/env.h>
#include <base/heap.h>
#include <base/allocator_avl.h>
#include <util/list.h>

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
		              Platform::Connection & platform);

		void * alloc(size_t size, size_t align);
		void * alloc_dma(size_t size, void ** dma_attr);
		size_t size(const void * ptr);
		void   free(const void * ptr);

	private:

		struct Dma_buffer : List<Dma_buffer>::Element
		{
			addr_t                   addr;
			size_t                   size;
			Ram_dataspace_capability cap;
			addr_t                   dma_addr;
		};

		Env                  & _env;
		Heap                 & _heap;
		Platform::Connection & _platform;
		Allocator_avl          _mem;
		List<Dma_buffer>       _dma_buffers {};
};

#endif /* _LX_KIT__MEMORY_H_ */
