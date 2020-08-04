/*
 * Copyright (c) 2008 Princeton University
 * Copyright (c) 2016 Georgia Institute of Technology
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Niket Agarwal
 *          Tushar Krishna
 */


#include "mem/ruby/network/garnet2.0/NetworkLink.hh"

#include "mem/ruby/network/garnet2.0/CreditLink.hh"

//++ Set default data for variables from parameters.
NetworkLink::NetworkLink(const Params *p)
    : ClockedObject(p), Consumer(this), m_id(p->link_id),
      m_type(NUM_LINK_TYPES_),
      m_latency(p->link_latency),
      linkBuffer(new flitBuffer()), link_consumer(nullptr),
      link_srcQueue(nullptr), m_link_utilized(0),
      m_vc_load(p->vcs_per_vnet * p->virt_nets)//++ TODO: m_vc_load is a vector, p->vcs_per_vnet * p->virt_nets is a int, why
{
}

NetworkLink::~NetworkLink()
{
    delete linkBuffer;
}

//++ Set the consumer pointer. TODO: Where does it point to.
void
NetworkLink::setLinkConsumer(Consumer *consumer)
{
    link_consumer = consumer;
}

//++ Set the source pointer. TODO: Where does it point to.
void
NetworkLink::setSourceQueue(flitBuffer *srcQueue)
{
    link_srcQueue = srcQueue;
}

//++ Transmission wake up.
void
NetworkLink::wakeup()
{
    //++ If source buffer is ready, wake up the link and start data transmission.
    if (link_srcQueue->isReady(curCycle())) {
        flit *t_flit = link_srcQueue->getTopFlit(); //++ Get first flit.
        t_flit->set_time(curCycle() + m_latency); //++ Set next wakeup time for the flit.
        linkBuffer->insert(t_flit); //++ Insert flit to link buffer.
        link_consumer->scheduleEventAbsolute(clockEdge(m_latency)); //++ Set wakeup time for link consumer.
        m_link_utilized++; //++ Increment utilization.
        m_vc_load[t_flit->get_vc()]++; //++ Increment virtual channel load.
    }
}

void
NetworkLink::resetStats()
{
    for (int i = 0; i < m_vc_load.size(); i++) {
        m_vc_load[i] = 0;
    }

    m_link_utilized = 0;
}

//++ Create a new NetworkLink.
NetworkLink *
NetworkLinkParams::create()
{
    return new NetworkLink(this);
}

//++ Create a new CreditLink.
CreditLink *
CreditLinkParams::create()
{
    return new CreditLink(this);
}

uint32_t
NetworkLink::functionalWrite(Packet *pkt)
{
    return linkBuffer->functionalWrite(pkt);
}
