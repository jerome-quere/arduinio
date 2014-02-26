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

#include <Arduino.h>
#include "IOService.h"

namespace aio
{
    static IOService*  g_instance;

    bool IOService::Event::operator<(const Event& e) const {
	unsigned long now = millis();
	return  timer.getTime(now) > e.timer.getTime(now);
    }

    IOService::IOService() {
	g_instance = this;
    }

    IOService::~IOService() {
	g_instance = NULL;
    }

    IOService& IOService::instance() {
	return *g_instance;
    }

    void IOService::addTimer(const unsigned long& time, Callback cb, void* data) {
	Event e = {TimePoint(time), cb, data};
	_heap.insert(e);
    }

    void IOService::_execOnce() {

	unsigned long now = millis();
	delay(_heap.top().timer.getTime(now));
	now += _heap.top().timer.getTime(now);
	while (_heap.size() && _heap.top().timer.isPast(now)) {
	    Event e = _heap.top();
	    _heap.pop();
	    e.cb(e.data);
	}
    }

    void IOService::exec() {
	_run = true;
	while (_run) {
	    _execOnce();
	}
    }
}
