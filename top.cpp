#include <time.h>
#include <systemc.h>

#include "router.h"
#include "pe.h"

int p1c=1,p2c=1,p3c=1,p4c=1,p5c=1,p6c=1,
	p7c=1,p8c=1,p9c=1,p10c=1,p11c=1,p12c=1,poc=1;

SC_MODULE(top)
{
public:
	enum {N = 3};   //N for horizontal
	enum {M = 3};	//M for vertical
	
	router *routers[N][M];	//REVISED BY LLK
	PE_base *pes[N][M];		//REVISED BY LLK

	sc_signal<packet> router_to_pe[N][M], pe_to_router[N][M];
	sc_signal<packet> router_to_router_east[N][M-1], router_to_router_west[N][M-1];
	sc_signal<packet> router_to_router_north[N-1][M], router_to_router_south[N-1][M];
	
	sc_signal<packet> terminal_loop_east[N], terminal_loop_west[N];
	sc_signal<packet> terminal_loop_north[M], terminal_loop_south[M];
	sc_signal<bool> clock;

	SC_CTOR(top)
	{
		create_pes();
		create_network();
	}

protected:
	void create_pes()
	{
		pes[0][0] = new PE_P11("P11");
		pes[0][0]->clock(clock);
		pes[0][0]->set_xy(0, 0);

		pes[1][0] = new PE_P4("P4");
		pes[1][0]->clock(clock);
		pes[1][0]->set_xy(0, 1);

		pes[2][0] = new PE_P7("P7");
		pes[2][0]->clock(clock);
		pes[2][0]->set_xy(0, 2);

		pes[0][1] = new PE_P1("P1");
		pes[0][1]->clock(clock);
		pes[0][1]->set_xy(1, 0);

		pes[1][1] = new PE_IO("PI/PO");
		pes[1][1]->clock(clock);
		pes[1][1]->set_xy(1, 1);

		pes[2][1] = new PE_P3("P3");
		pes[2][1]->clock(clock);
		pes[2][1]->set_xy(1, 2);

		pes[0][2] = new PE_P5("P5");
		pes[0][2]->clock(clock);
		pes[0][2]->set_xy(2, 0);

		pes[1][2] = new PE_P2("P2");
		pes[1][2]->clock(clock);
		pes[1][2]->set_xy(2, 1);

		pes[2][2] = new PE_P9("P9");
		pes[2][2]->clock(clock);
		pes[2][2]->set_xy(2, 2);
		
	}

	void create_network()
	{
		for (int i = 0; i < M; ++i)
		{

			for (int j = 0; j < N; ++j)
			{
			char name[100];
			sprintf(name, "router(%d,%d)", i,j);

			// create router
			routers[j][i] = new router(name);
			routers[j][i]->set_xy(i,j);
			routers[j][i]->clock(clock);

			if(j!=0)	// connect router to north routers
			{
				routers[j][i]->port_out[router::NORTH](
					router_to_router_north[j-1][i]);
				routers[j][i]->port_in[router::NORTH](
					router_to_router_south[j-1][i]);
			}
			else	//or make a loop
			{
				routers[j][i]->port_out[router::NORTH](
					terminal_loop_north[i]);
				routers[j][i]->port_in[router::NORTH](
					terminal_loop_north[i]);
			}
			if(j !=N-1)	// connect router to south routers
			{
				routers[j][i]->port_out[router::SOUTH](
					router_to_router_south[j][i]);
				routers[j][i]->port_in[router::SOUTH](
					router_to_router_north[j][i]);
			}
			else	// or make a loop
			{
				routers[j][i]->port_out[router::SOUTH](
					terminal_loop_south[i]);
				routers[j][i]->port_in[router::SOUTH](
					terminal_loop_south[i]);
			}

			// connect router to west routers
			if (i != 0)
			{
				routers[j][i]->port_out[router::WEST](
					router_to_router_west[j][i-1]);
				routers[j][i]->port_in[router::WEST](
					router_to_router_east[j][i-1]);
			}
			else // or make a loop
			{
				routers[j][i]->port_out[router::WEST](
					terminal_loop_west[j]);
				routers[j][i]->port_in[router::WEST](
					terminal_loop_west[j]);
			}

			if (i != M-1) // connect router to east routers
			{
				routers[j][i]->port_out[router::EAST](
					router_to_router_east[j][i]);
				routers[j][i]->port_in[router::EAST](
					router_to_router_west[j][i]);
			}
			else // or make a loop
			{
				routers[j][i]->port_out[router::EAST](
					terminal_loop_east[j]);
				routers[j][i]->port_in[router::EAST](
					terminal_loop_east[j]);
			}

			// connect router to PE
			routers[j][i]->port_out[router::PE](router_to_pe[j][i]);
			routers[j][i]->port_in[router::PE](pe_to_router[j][i]);
			pes[j][i]->data_in(router_to_pe[j][i]);
			pes[j][i]->data_out(pe_to_router[j][i]);

			}
		}
	}

}; // top

int sc_main(int argc , char *argv[])
{
	srand(0);

	top top_module("top");

	printf("cycle  0 ================================\n");
	sc_start(0, SC_NS);

	for(int i = 1; i < 200; i++){
		
		printf("cycle %2d ================================\n", i);

		top_module.clock.write(1);
		sc_start(10, SC_NS);
		top_module.clock.write(0);
		sc_start(10, SC_NS);
	}
	system("pause");
	return 0;
}
