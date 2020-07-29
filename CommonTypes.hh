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


#ifndef __MEM_RUBY_NETWORK_GARNET_COMMONTYPES_HH__
#define __MEM_RUBY_NETWORK_GARNET_COMMONTYPES_HH__

#include "mem/ruby/common/NetDest.hh"

// All common enums and typedefs go here

//++ Indicate the type of flit. There are four types.
//++ HEAD_: Flit header. First flit of the packet.
//++ BODY_: Data of the packet.
//++ TAIL_: Last flit of the packet.
//++ HEAD_TAIL_: Single flit packet.
enum flit_type {HEAD_, BODY_, TAIL_, HEAD_TAIL_, NUM_FLIT_TYPE_};

//++ Indicate the state of the virtual channel.
//++ IDLE_: Idle state.
//++ VC_AB_: TODO
//++ ACTIVE_: TODO
enum VC_state_type {IDLE_, VC_AB_, ACTIVE_, NUM_VC_STATE_TYPE_};

//++ Indicate the type of the virtual net.
//++ CTRL_VNET: TODO
//++ DATA_VNET_: TODO
//++ NULL_VNET_: TODO
enum VNET_type {CTRL_VNET_, DATA_VNET_, NULL_VNET_, NUM_VNET_TYPE_};

//++ Indicate the stage of current flit in a router.
//++ I_: Inpute.
//++ VA_: Virtual Channel Allocation.
//++ SA_: Switch Allocation.
//++ ST_: Switch Traversal.
//++ LT_: Link Traversal.
enum flit_stage {I_, VA_, SA_, ST_, LT_, NUM_FLIT_STAGE_};

//++ Indicate the type of a link.
//++ EXT_IN_: TODO
//++ EXT_OUT_: TODO
//++ INT_: TODO
enum link_type { EXT_IN_, EXT_OUT_, INT_, NUM_LINK_TYPES_ };

//++ Indicate the routing algorithm.
//++ TABLE_: Table based routing. TODO
//++ XY_: TODO
//++ TURN_MODEL_: TODO
//++ RANDOM_: TODO
//++ CUSTOM_: TODO
enum RoutingAlgorithm { TABLE_ = 0, XY_ = 1, TURN_MODEL_ = 2, RANDOM_ = 3,
                        CUSTOM_ = 4,
                        NUM_ROUTING_ALGORITHM_};


//++ Routing information
struct RouteInfo
{
    // destination format for table-based routing
    int vnet;         //++ Virtual net
    NetDest net_dest; //++ TODO

    // src and dest format for topology-specific routing
    int src_ni;       //++ Source network interface.
    int src_router;   //++ Source router. In garnet, src_ni and src_router are not equal.
                      //++ One router could have multiple network interface.
    int dest_ni;      //++ Destination network interface.
    int dest_router;  //++ Destination router
    int hops_traversed; //++ Number of total hops. TODO: for packet or flit? including ni?
};


//++ TODO
#define INFINITE_ 10000

#endif // __MEM_RUBY_NETWORK_GARNET_COMMONTYPES_HH__
