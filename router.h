#ifndef ROUTER_H
#define ROUTER_H

#include <systemc.h>
#include <list>

// a empty packet has src_x == src_y == dest_x == dest_y == -1

struct complex			//define a struct for cpmplex number
{
	double re,im;
};

typedef complex token_type;
struct packet
{
	int src_x, src_y;
	int dest_x, dest_y;
	token_type  token;

	packet(int sx = -1, int sy = -1, int dx = -1, int dy = -1,
		token_type t = token_type())
		: src_x(sx), src_y(sy), dest_x(dx), dest_y(dy), token(t)
	{
	}

	bool operator==(const packet &x) const
	{
		return (x.src_x == src_x) && (x.src_y == src_y)
			&& (x.dest_x == dest_x) && (x.dest_y == dest_y)
			&& (x.token.re == token.re)&&
			   (x.token.im == token.im); 
	}
}; // struct packet

std::ostream &operator<<(std::ostream &o, const packet &p);
void sc_trace(sc_trace_file *tf, const packet &p, const std::string &name);

SC_MODULE(router)
{
	sc_in<bool> clock; // port for the global clock

	enum {PE = 0, NORTH, SOUTH, EAST, WEST, PORTS};
	sc_in<packet> port_in[PORTS]; // input ports	REVISED LLK
	sc_out<packet> port_out[PORTS]; // output ports	REVISED LLK

	void main(); // specify the functionality of router per clock cycle

	SC_CTOR(router)
		: x_(-1), y_(-1)
	{
		SC_METHOD(main);
		sensitive << clock.pos();
	}

	// use this function to set the coordinates of the router
	void set_xy(int x, int y);

protected:
	std::list<packet> out_queue_[PORTS]; // output queues	REVISED BY LLK

	int x_, y_; // location of the router

	void read_packet(int iport); // read a packet from the link
	void write_packet(int iport); // write a packet to the link
	void route_packet_xy(packet p); // route the packet to the output queue
}; // router

#endif // ROUTER_H
