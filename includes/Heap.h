/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Jerome Quere <contact@jeromequere.com>
 *
 * Permission is hereby granted, free  of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction,  including without limitation the rights
 * to use,  copy,  modify,  merge, publish,  distribute, sublicense, and/or sell
 * copies  of  the  Software,  and  to  permit  persons  to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The  above  copyright  notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED  "AS IS",  WITHOUT WARRANTY  OF ANY KIND, EXPRESS OR
 * IMPLIED,  INCLUDING BUT NOT LIMITED  TO THE  WARRANTIES  OF  MERCHANTABILITY,
 * FITNESS  FOR A  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS  OR  COPYRIGHT  HOLDERS  BE  LIABLE  FOR  ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT  OF  OR  IN  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _AIO_HEAP_H_
#define _AIO_HEAP_H_

namespace aio
{
    template <typename T, unsigned long MAXSIZE>
    class Heap
    {
    public:

	typedef T* iterator;
	typedef T* const_iterator;

	Heap();
	iterator insert(const T& obj);
	T& top();
	const T& top() const;
	void pop();
	const unsigned long& size() const;

	iterator begin();
	const_iterator begin() const;

	iterator end();
	const_iterator end() const;

    private:

	void		_swap(const unsigned long& idx1, const unsigned long& idx2);
	void		_moveUp(const unsigned long& idx);
	void		_moveDown(const unsigned long& idx);
	inline unsigned int	_leftIdx(const unsigned int& idx);
	inline unsigned int	_rightIdx(const unsigned int& idx);
	inline unsigned int	_parentIdx(const unsigned int& idx);

	unsigned long		_size;
	T			_data[MAXSIZE];
    };
}

#include "Heap.hpp"

#endif
