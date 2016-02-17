#include "pe.h"
#include <math.h>
extern int p1c,p2c,p3c,p4c,p5c,p6c,p7c,p8c,p9c,p10c,p11c,p12c,poc;
token_type x0in,x1in,x2in,x3in,x4in,x5in,x6in,x7in,
	       y0in,y1in,y2in,y3in,y4in,y5in,y6in,y7in,
		   y0out,y1out,y2out,y3out,y4out,y5out,y6out,y7out,
		   z0in,z1in,z2in,z3in,z4in,z5in,z6in,z7in,
		   z0out,z1out,z2out,z3out,z4out,z5out,z6out,z7out,
		   X0in,X1in,X2in,X3in,X4in,X5in,X6in,X7in,
		   X0out,X1out,X2out,X3out,X4out,X5out,X6out,X7out;

struct wstruct w1,w2,w3;
int pifire=1,pofire=1;

void PE_base::set_xy(int x, int y)
{
	assert((x_ == -1) && (y_ == -1)); // set once only
	assert((x != -1) && (y != -1)); // must use a legal location
	
	x_ = x;
	y_ = y;
	w1.wre=sqrt(2.0000)/2.0000;
	w1.wim=-sqrt(2.0000)/2.0000;
	w2.wre=0.0000;
	w2.wim=-1.0000;
	w3.wre=-sqrt(2.0000)/2.0000;
	w3.wim=-sqrt(2.0000)/2.0000;
}

void PE_base::read_input()
{
	packet_in_ = data_in.read();
}

void PE_base::write_output()
{
	if (out_queue_.empty())
	{
		data_out.write(packet());
	}
	else
	{
		data_out.write(out_queue_.front());
		out_queue_.pop_front();
	}
}

void PE_IO::execute()
{		if(pifire<=1)
		fire_PI();

	// fire PO if the incoming packet is valid
	if ((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1))
		fire_PO();
}

void PE_IO::fire_PI()
{	
	token_type x0,x1,x2,x3,x4,x5,x6,x7;
	x0.re=(rand()%10000)/10000.0000; x0.im=(rand()%10000)/10000.0000;
	x1.re=(rand()%10000)/10000.0000; x1.im=(rand()%10000)/10000.0000;
	x2.re=(rand()%10000)/10000.0000; x2.im=(rand()%10000)/10000.0000;
	x3.re=(rand()%10000)/10000.0000; x3.im=(rand()%10000)/10000.0000;
	x4.re=(rand()%10000)/10000.0000; x4.im=(rand()%10000)/10000.0000;
	x5.re=(rand()%10000)/10000.0000; x5.im=(rand()%10000)/10000.0000;
	x6.re=(rand()%10000)/10000.0000; x6.im=(rand()%10000)/10000.0000;
	x7.re=(rand()%10000)/10000.0000; x7.im=(rand()%10000)/10000.0000;
	
	packet p0(x_, y_, 1, 0, x0);
	printf("Round %d:PI: send x0 %.4f+%.4fi to (%d,%d)\n",
		pifire,x0.re,x0.im, p0.dest_x, p0.dest_y);
	packet p1(x_, y_, 1, 2, x1);
	printf("Round %d:PI: send x1 %.4f+%.4fi to (%d,%d)\n",
		pifire,x1.re,x1.im, p1.dest_x, p1.dest_y);
	packet p2(x_, y_, 2, 1, x2);
	printf("Round %d:PI: send x2 %.4f+%.4fi to (%d,%d)\n",
		pifire,x2.re,x2.im, p2.dest_x, p2.dest_y);
	packet p3(x_, y_, 0, 1, x3);
	printf("Round %d:PI: send x3 %.4f+%.4fi to (%d,%d)\n",
		pifire,x3.re,x3.im, p3.dest_x, p3.dest_y);
	packet p4(x_, y_, 1, 0, x4);
	printf("Round %d:PI: send x4 %.4f+%.4fi to (%d,%d)\n",
		pifire,x4.re,x4.im, p4.dest_x, p4.dest_y);
	packet p5(x_, y_, 1, 2, x5);
	printf("Round %d:PI: send x5 %.4f+%.4fi to (%d,%d)\n",
		pifire,x5.re,x5.im, p5.dest_x, p5.dest_y);
	packet p6(x_, y_, 2, 1, x6);
	printf("Round %d:PI: send x6 %.4f+%.4fi to (%d,%d)\n",
		pifire,x6.re,x6.im, p6.dest_x, p6.dest_y);
	packet p7(x_, y_, 0, 1, x7);
	printf("Round %d:PI: send x7 %.4f+%.4fi to (%d,%d)\n",
		pifire,x7.re,x7.im, p7.dest_x, p7.dest_y);
	out_queue_.push_back(p0);
	out_queue_.push_back(p1);
	out_queue_.push_back(p2);
	out_queue_.push_back(p3);
	out_queue_.push_back(p4);
	out_queue_.push_back(p5);
	out_queue_.push_back(p6);
	out_queue_.push_back(p7);
	
	pifire++;
}

void PE_IO::fire_PO()
{
	assert((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1));
	if(poc%8==1)
	{
		printf("Round %d:PO: receive X(0)= %.4f+%.4fi from (%d,%d)\n",
		pofire,packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,packet_in_.src_y);
	}
	if(poc%8==2)
	{
		printf("Round %d:PO: receive X(4)= %.4f+%.4fi from (%d,%d)\n",
		pofire,packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,packet_in_.src_y);
	}
	if(poc%8==3)
	{
		printf("Round %d:PO: receive X(2)= %.4f+%.4fi from (%d,%d)\n",
		pofire,packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,packet_in_.src_y);
	}
	if(poc%8==4)
	{
		printf("Round %d:PO: receive X(1)= %.4f+%.4fi from (%d,%d)\n",
		pofire,packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,packet_in_.src_y);
	}
	if(poc%8==5)
	{
		printf("Round %d:PO: receive X(6)= %.4f+%.4fi from (%d,%d)\n",
		pofire,packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,packet_in_.src_y);
	}
	if(poc%8==6)
	{
		printf("Round %d:PO: receive X(5)= %.4f+%.4fi from (%d,%d)\n",
		pofire,packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,packet_in_.src_y);
	}
	if(poc%8==7)
	{
		printf("Round %d:PO: receive X(3)= %.4f+%.4fi from (%d,%d)\n",
		pofire,packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,packet_in_.src_y);
	}
	if(poc%8==0)
	{
		printf("Round %d:PO: receive X(7)= %.4f+%.4fi from (%d,%d)\n",
		pofire,packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,packet_in_.src_y);
		pofire++;
	}
	poc+=1;

//	printf("PO: receive %.4f+%.4fi from (%d,%d)\n",
//		packet_in_.token.re,packet_in_.token.im, packet_in_.src_x,	packet_in_.src_y);
}

void PE_P1::execute()
{
	// fire the actor if the incoming packet is valid
	if ((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1))
		fire();
}

void PE_P1::fire()
{
	assert((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1));
	//token_type x0in,x4in,y0out,y1out;
	if(p1c%2==1)
	{
		printf("P1(%d,%d): receive x0 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	x0in.re=packet_in_.token.re;
	x0in.im=packet_in_.token.im;
	}
	if(p1c%2==0)
	{
	x4in.re=packet_in_.token.re;
	x4in.im=packet_in_.token.im;
	printf("P1(%d,%d): receive x4 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	
	y0out.re=x0in.re+x4in.re;
	y0out.im=x0in.im+x4in.im;
	y1out.re=x0in.re-x4in.re;
	y1out.im=x0in.im-x4in.im;
	packet py0(x_, y_, 2, 0, y0out);
	printf("P1 send y0=%.4f+%.4fi to (%d,%d)\n",
	py0.token.re,py0.token.im, 2, 0);
	out_queue_.push_back(py0);
	packet py1(x_, y_, 2, 0, y1out);
	printf("P1 send y1=%.4f+%.4fi to (%d,%d)\n",
	py1.token.re,py1.token.im, 2, 0);
	out_queue_.push_back(py1);
	}
	p1c=p1c+1;
}

void PE_P2::execute()
{
	// fire the actor if the incoming packet is valid
	if ((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1))
		fire();
}

void PE_P2::fire()
{
	assert((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1));

	if(p2c%2==1)
	{
		x2in.re=packet_in_.token.re;
		x2in.im=packet_in_.token.im;
		printf("P2(%d,%d): receive x2 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	}
	if(p2c%2==0)
	{
	x6in.re=packet_in_.token.re;
	x6in.im=packet_in_.token.im;
	printf("P2(%d,%d): receive x6 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	printf("x2=%.4f+%.4fi,x6=%.4f+%.4fi\n",x2in.re,x2in.im,x6in.re,x6in.im);
	y2out.re=x2in.re+x6in.re;
	y2out.im=x2in.im+x6in.im;
	y3out.re=x2in.re-x6in.re;
	y3out.im=x2in.im-x6in.im;
	printf("y2=%.4f+%.4fi,y3=%.4f+%.4fi\n",y2out.re,y2out.im,y3out.re,y3out.im);
	packet py2(x_, y_, 2, 0, y2out);
	printf("P2 send y2=%.4f+%.4fi to (%d,%d)\n",
	py2.token.re,py2.token.im, 2, 0);
	out_queue_.push_back(py2);
	packet py3(x_, y_, 2, 0, y3out);
	printf("P2 send y3=%.4f+%.4fi to (%d,%d)\n",
	py3.token.re,py3.token.im, 2, 0);
	out_queue_.push_back(py3);
	}
	p2c=p2c+1;
}

void PE_P3::execute()
{
	// fire the actor if the incoming packet is valid
	if ((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1))
		fire();
}

void PE_P3::fire()
{
	assert((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1));

	if(p3c%2==1)
	{
		printf("P3(%d,%d): receive x1 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	x1in.re=packet_in_.token.re;
	x1in.im=packet_in_.token.im;
	}
	if(p3c%2==0)
	{
	x5in.re=packet_in_.token.re;
	x5in.im=packet_in_.token.im;
	printf("P3(%d,%d): receive x5 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	printf("x1=%.4f+%.4fi,x5=%.4f+%.4fi\n",x1in.re,x1in.im,x5in.re,x5in.im);
	
	y4out.re=x1in.re+x5in.re;
	y4out.im=x1in.im+x5in.im;
	y5out.re=x1in.re-x5in.re;
	y5out.im=x1in.im-x5in.im;
	packet py4(x_, y_, 0, 2, y4out);
	printf("P3 send y4=%.4f+%.4fi to (%d,%d)\n",
	py4.token.re,py4.token.im, 0, 2);
	out_queue_.push_back(py4);
	packet py5(x_, y_, 0, 2, y5out);
	printf("P3 send y5=%.4f+%.4fi to (%d,%d)\n",
	py5.token.re,py5.token.im, 0, 2);
	out_queue_.push_back(py5);
	}
	p3c=p3c+1;
}

void PE_P4::execute()
{
	// fire the actor if the incoming packet is valid
	if ((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1))
		fire();
}

void PE_P4::fire()
{
	assert((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1));

	if(p4c%2==1)
	{
		printf("P4(%d,%d): receive x3 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	x3in.re=packet_in_.token.re;
	x3in.im=packet_in_.token.im;
	}
	if(p4c%2==0)
	{
	x7in.re=packet_in_.token.re;
	x7in.im=packet_in_.token.im;
	printf("P4(%d,%d): receive x7 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	
	y6out.re=x3in.re+x7in.re;
	y6out.im=x3in.im+x7in.im;
	y7out.re=x3in.re-x7in.re;
	y7out.im=x3in.im-x7in.im;
	packet py6(x_, y_, 0, 2, y6out);
	printf("P4 send y6=%.4f+%.4fi to (%d,%d)\n",
	py6.token.re,py6.token.im, 0, 2);
	out_queue_.push_back(py6);
	packet py7(x_, y_, 0, 2, y7out);
	printf("P4 send y7=%.4f+%.4fi to (%d,%d)\n",
	py7.token.re,py7.token.im, 0, 2);
	out_queue_.push_back(py7);
	}
	p4c=p4c+1;
}

void PE_P5::execute()
{
	// fire the actor if the incoming packet is valid
	if ((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1))
		fire();
}
void PE_P5::fire()
{
	assert((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1));

	if(p5c%4==1)
	{
		printf("P5(%d,%d): receive y0 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	y0in.re=packet_in_.token.re;
	y0in.im=packet_in_.token.im;
	}
	if(p5c%4==2)
	{
		printf("P5(%d,%d): receive y1 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	y1in.re=packet_in_.token.re;
	y1in.im=packet_in_.token.im;
	}
	if(p5c%4==3)
	{
		printf("P5(%d,%d): receive y2 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	y2in.re=packet_in_.token.re;
	y2in.im=packet_in_.token.im;
	}
	if(p5c%4==0)
	{
	y3in.re=packet_in_.token.re;
	y3in.im=packet_in_.token.im;
	printf("P5(%d,%d): receive y3 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	
	z0out.re=y0in.re+y2in.re;
	z0out.im=y0in.im+y2in.im;
	z1out.re=y0in.re-y2in.re;
	z1out.im=y0in.im-y2in.im;
	z2out.re=y1in.re+y3in.im;
	z2out.im=y1in.im-y3in.re;
	z3out.re=y1in.re-y3in.im;
	z3out.im=y1in.im+y3in.re;
	packet pz0(x_, y_, 2, 2, z0out);
	printf("P5 send z0=%.4f+%.4fi to (%d,%d)\n",
	pz0.token.re,pz0.token.im, 2, 2);
	out_queue_.push_back(pz0);
	packet pz1(x_, y_, 0, 0, z1out);
	printf("P5 send z1=%.4f+%.4fi to (%d,%d)\n",
	pz1.token.re,pz1.token.im, 0, 0);
	out_queue_.push_back(pz1);
	packet pz2(x_, y_, 2, 2, z2out);
	printf("P6 send z2=%.4f+%.4fi to (%d,%d)\n",
	pz2.token.re,pz2.token.im, 2, 2);
	out_queue_.push_back(pz2);
	packet pz3(x_, y_, 0, 0, z3out);
	printf("P6 send z3=%.4f+%.4fi to (%d,%d)\n",
	pz3.token.re,pz3.token.im, 0, 0);
	out_queue_.push_back(pz3);
	}
	p5c=p5c+1;
	
}

void PE_P7::execute()
{
	// fire the actor if the incoming packet is valid
	if ((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1))

		fire();
}
void PE_P7::fire()
{
	assert((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1));

	if(p7c%4==1)
	{
		printf("P7(%d,%d): receive y4 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	y4in.re=packet_in_.token.re;
	y4in.im=packet_in_.token.im;
	}
	if(p7c%4==2)
	{
		printf("P7(%d,%d): receive y5 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	y5in.re=packet_in_.token.re;
	y5in.im=packet_in_.token.im;
	}
	if(p7c%4==3)
	{
		printf("P7(%d,%d): receive y6 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	y6in.re=packet_in_.token.re;
	y6in.im=packet_in_.token.im;
	}
	if(p7c%4==0)
	{
	y7in.re=packet_in_.token.re;
	y7in.im=packet_in_.token.im;
	printf("P7(%d,%d): receive y7 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	
	z4out.re=y4in.re+y6in.re;
	z4out.im=y4in.im+y6in.im;
	z5out.re=y4in.re-y6in.re;
	z5out.im=y4in.im-y6in.im;
	z6out.re=y5in.re+y7in.im;
	z6out.im=y5in.im-y7in.re;
	z7out.re=y5in.re-y7in.im;
	z7out.im=y5in.im+y7in.re;
	packet pz4(x_, y_, 2, 2, z4out);
	printf("P7 send z4=%.4f+%.4fi to (%d,%d)\n",
	pz4.token.re,pz4.token.im, 2, 2);
	out_queue_.push_back(pz4);
	packet pz5(x_, y_, 0, 0, z5out);
	printf("P7 send z5=%.4f+%.4fi to (%d,%d)\n",
	pz5.token.re,pz5.token.im, 0, 0);
	out_queue_.push_back(pz5);
	packet pz6(x_, y_, 2, 2, z6out);
	printf("P8 send z6=%.4f+%.4fi to (%d,%d)\n",
	pz6.token.re,pz6.token.im, 2, 2);
	out_queue_.push_back(pz6);
	packet pz7(x_, y_, 0, 0, z7out);
	printf("P8 send z7=%.4f+%.4fi to (%d,%d)\n",
	pz7.token.re,pz7.token.im, 0, 0);
	out_queue_.push_back(pz7);
	}
	p7c=p7c+1;
	
}

void PE_P9::execute()
{
	// fire the actor if the incoming packet is valid
	if ((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1))
		fire();
}
void PE_P9::fire()
{
	assert((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1));

	if(p9c%4==1)
	{
		printf("P9(%d,%d): receive z0 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	z0in.re=packet_in_.token.re;
	z0in.im=packet_in_.token.im;
	}
	if(p9c%4==2)
	{
		printf("P9(%d,%d): receive z4 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	z4in.re=packet_in_.token.re;
	z4in.im=packet_in_.token.im;
	}
	if(p9c%4==3)
	{
		printf("P9(%d,%d): receive z2 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	z2in.re=packet_in_.token.re;
	z2in.im=packet_in_.token.im;
	}
	if(p9c%4==0)
	{
	z6in.re=packet_in_.token.re;
	z6in.im=packet_in_.token.im;
	printf("P9(%d,%d): receive z6 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	
	X0out.re=z0in.re+z4in.re;
	X0out.im=z0in.im+z4in.im;
	X4out.re=z0in.re-z4in.re;
	X4out.im=z0in.im-z4in.im;
	X1out.re=z2in.re+(z6in.re*w1.wre-z6in.im*w1.wim);
	X1out.im=z2in.im+(z6in.re*w1.wim+z6in.im*w1.wre);
	X5out.re=z2in.re-(z6in.re*w1.wre-z6in.im*w1.wim);
	X5out.im=z2in.im-(z6in.re*w1.wim+z6in.im*w1.wre);
	packet pX0(x_, y_, 1, 1, X0out);
	printf("P9 send X0=%.4f+%.4fi to (%d,%d)\n",
	pX0.token.re,pX0.token.im, 1, 1);
	out_queue_.push_back(pX0);
	packet pX4(x_, y_, 1, 1, X4out);
	printf("P9 send X4=%.4f+%.4fi to (%d,%d)\n",
	pX4.token.re,pX4.token.im, 1, 1);
	out_queue_.push_back(pX4);
	packet pX1(x_, y_, 1, 1, X1out);
	printf("P10 send X1=%.4f+%.4fi to (%d,%d)\n",
	pX1.token.re,pX1.token.im, 1, 1);
	out_queue_.push_back(pX1);
	packet pX5(x_, y_, 1, 1, X5out);
	printf("P10 send X5=%.4f+%.4fi to (%d,%d)\n",
	pX5.token.re,pX5.token.im, 1, 1);
	out_queue_.push_back(pX5);
	}
	p9c=p9c+1;

}

void PE_P11::execute()
{
	// fire the actor if the incoming packet is valid
	if ((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1))

		fire();
}
void PE_P11::fire()
{
	assert((packet_in_.src_x != -1)
		&& (packet_in_.src_y != -1));

	if(p11c%4==1)
	{
		printf("P11(%d,%d): receive z1 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	z1in.re=packet_in_.token.re;
	z1in.im=packet_in_.token.im;
	}
	if(p11c%4==2)
	{
		printf("P11(%d,%d): receive z5 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	z5in.re=packet_in_.token.re;
	z5in.im=packet_in_.token.im;
	}
	if(p11c%4==3)
	{
		printf("P11(%d,%d): receive z3 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	z3in.re=packet_in_.token.re;
	z3in.im=packet_in_.token.im;
	}
	if(p11c%4==0)
	{
	z7in.re=packet_in_.token.re;
	z7in.im=packet_in_.token.im;
	printf("P11(%d,%d): receive z7 %.4f+%.4fi from (%d,%d)\n",
		x_, y_,
		packet_in_.token.re,packet_in_.token.im,packet_in_.src_x,	packet_in_.src_y
		);
	
	X2out.re=z1in.re+z5in.im;
	X2out.im=z1in.im-z5in.re;
	X6out.re=z1in.re-z5in.im;
	X6out.im=z1in.im+z5in.re;
	X3out.re=z3in.re+(z7in.re*w3.wre-z7in.im*w3.wim);
	X3out.im=z3in.im+(z7in.re*w3.wim+z7in.im*w3.wre);
	X7out.re=z3in.re-(z7in.re*w3.wre-z7in.im*w3.wim);
	X7out.im=z3in.im-(z7in.re*w3.wim+z7in.im*w3.wre);
	packet pX2(x_, y_, 1, 1, X2out);
	printf("P11 send X2=%.4f+%.4fi to (%d,%d)\n",
	pX2.token.re,pX2.token.im, 1, 1);
	out_queue_.push_back(pX2);
	packet pX6(x_, y_, 1, 1, X6out);
	printf("P11 send X6=%.4f+%.4fi to (%d,%d)\n",
	pX6.token.re,pX6.token.im, 1, 1);
	out_queue_.push_back(pX6);
	packet pX3(x_, y_, 1, 1, X3out);
	printf("P12 send x3=%.4f+%.4fi to (%d,%d)\n",
	pX3.token.re,pX3.token.im, 1, 1);
	out_queue_.push_back(pX3);
	packet pX7(x_, y_, 1, 1, X7out);
	printf("P12 send x7=%.4f+%.4fi to (%d,%d)\n",
	pX7.token.re,pX7.token.im, 1, 1);
	out_queue_.push_back(pX7);
	}
	p11c=p11c+1;
	
}
