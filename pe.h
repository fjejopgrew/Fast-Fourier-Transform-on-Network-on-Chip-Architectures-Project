#ifndef PE_H
#define PE_H

#include "router.h"

struct wstruct
{
	double wre,wim;
};

SC_MODULE(PE_base)
{
	sc_in<bool> clock; // port for the global clock

	sc_in<packet> data_in; // from router
	sc_out<packet> data_out; // to router

	void main() // specify the functionality of PE per clock cycle
	{
		read_input();
		execute();
		write_output();
	}

	SC_CTOR(PE_base)
		: x_(-1), y_(-1)
	{
		SC_METHOD(main);
		sensitive << clock.pos();
	}

	// use this function to set the coordinates of the PE
	void set_xy(int x, int y);

	virtual ~PE_base() {}

protected:
	std::list<packet> out_queue_; // output queue
	packet packet_in_; // incoming packet from the router

	int x_, y_; // location of the PE

	virtual void read_input(); // read a packet from the the router
	virtual void execute() = 0; // abstraction of computations
	virtual void write_output(); // // send a packet to the router
}; // PE_base

// for PI and PO
class PE_IO : public PE_base
{
public:
	PE_IO(const char *name) : PE_base(name) {}

protected:
	void execute();
	void fire_PI();
	void fire_PO();
}; // class PE_IO

// for P1
class PE_P1 : public PE_base
{
public:
	PE_P1(const char *name) : PE_base(name) {}

protected:
	void execute();
	void fire();
};
class PE_P2 : public PE_base
{
public:
	PE_P2(const char *name) : PE_base(name) {}

protected:
	void execute();
	void fire();
};
class PE_P3 : public PE_base
{
public:
	PE_P3(const char *name) : PE_base(name) {}

protected:
	void execute();
	void fire();
};
class PE_P4 : public PE_base
{
public:
	PE_P4(const char *name) : PE_base(name) {}

protected:
	void execute();
	void fire();
};
class PE_P5 : public PE_base
{
public:
	PE_P5(const char *name) : PE_base(name) {}

protected:
	void execute();
	void fire();

};

class PE_P7 : public PE_base
{
public:
	PE_P7(const char *name) : PE_base(name) {}

protected:
	void execute();
	void fire();
};

class PE_P9 : public PE_base
{
public:
	PE_P9(const char *name) : PE_base(name) {}

protected:
	void execute();
	void fire();

};

class PE_P11 : public PE_base
{
public:
	PE_P11(const char *name) : PE_base(name) {}

protected:
	void execute();
	void fire();
};
#endif // PE_H
