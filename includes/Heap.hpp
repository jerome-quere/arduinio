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

#ifndef _AIO_HEAP_HPP_
#define _AIO_HEAP_HPP_

namespace aio
{
    template <typename T, unsigned long MAXSIZE>
    Heap<T, MAXSIZE>::Heap() {
	_size = 0;
    }

    template <typename T, unsigned long MAXSIZE>
    typename Heap<T, MAXSIZE>::iterator Heap<T, MAXSIZE>::insert(const T& obj) {
	if (_size >= MAXSIZE)
	    return end();
	_data[_size] = obj;
	_size++;
	_moveDown(_size - 1);
	return (end() - 1);
    }

    template <typename T, unsigned long MAXSIZE>
    T& Heap<T, MAXSIZE>::top() {
	return _data[0];
    }

    template <typename T, unsigned long MAXSIZE>
    const T& Heap<T, MAXSIZE>::top() const {
	return _data[0];
    }

    template <typename T, unsigned long MAXSIZE>
    void Heap<T, MAXSIZE>::pop() {
	_data[0] = _data[_size - 1];
	_size--;
	_moveUp(0);
    }

    template <typename T, unsigned long MAXSIZE>
    void Heap<T, MAXSIZE>::_swap(const unsigned long& idx1, const unsigned long& idx2) {
	T tmp;

	tmp = _data[idx1];
	_data[idx1] = _data[idx2];
	_data[idx2] = tmp;
    }

    template <typename T, unsigned long MAXSIZE>
    void Heap<T, MAXSIZE>::_moveDown(const unsigned long& idx) {
	if (idx <= 0)
	    return;
	unsigned long parent = _parentIdx(idx);
	if (_data[parent] < _data[idx])
	    {
		_swap(parent, idx);
		_moveDown(parent);
	    }
    }

    template <typename T, unsigned long MAXSIZE>
    void Heap<T, MAXSIZE>::_moveUp(const unsigned long& idx) {
	if (_size == 0 || idx >= _size - 1)
	    return;

	unsigned int _left = _leftIdx(idx);
	unsigned int _right = _rightIdx(idx) >= _size ? idx : _rightIdx(idx);

	unsigned int max = (_data[_right] < _data[_left]) ? _left : _right;
	if (_data[idx] < _data[max] && idx != max)
	    {
		_swap(idx, max);
		_moveUp(max);
	    }
    }

    template <typename T, unsigned long MAXSIZE>
    const unsigned long& Heap<T, MAXSIZE>::size() const {
	return _size;
    }

    template <typename T, unsigned long MAXSIZE>
    typename Heap<T, MAXSIZE>::iterator Heap<T, MAXSIZE>::begin() {
	return _data;
    }

    template <typename T, unsigned long MAXSIZE>
    typename Heap<T, MAXSIZE>::const_iterator Heap<T, MAXSIZE>::begin() const {
	return _data;
    }

    template <typename T, unsigned long MAXSIZE>
    typename Heap<T, MAXSIZE>::iterator Heap<T, MAXSIZE>::end() {
	return _data + size() + 1;
    }

    template <typename T, unsigned long MAXSIZE>
    typename Heap<T, MAXSIZE>::const_iterator Heap<T, MAXSIZE>::end() const {
	return _data + size() + 1;
    }

    template <typename T, unsigned long MAXSIZE>
    inline unsigned int Heap<T, MAXSIZE>::_leftIdx(const unsigned int& idx) {
	return ((idx + 1) * 2) - 1;
    }

    template <typename T, unsigned long MAXSIZE>
    inline unsigned int Heap<T, MAXSIZE>::_rightIdx(const unsigned int& idx) {
	return (idx + 1) * 2;
    }

    template <typename T, unsigned long MAXSIZE>
    inline unsigned int Heap<T, MAXSIZE>::_parentIdx(const unsigned int& idx) {
	return ( (idx + 1) / 2) - 1;
    }
}


#endif
