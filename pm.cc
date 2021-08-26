namespace nforms{
	// -------------------------------------
	// TOPE 3D
	// -------------------------------------
	#define trunk_cb(d) [](int d)->void
	void trunk(int d, int maxd, std::function<void(int)> fun)
	{
		begintk;
		fun(d);

		if (d < maxd)
			trunk(d + 1, maxd, fun);
		endtk;
	}
	void trunk(int d = 0)
	{
		begintk;
			rot(blend(-10, 10, d / 13.), coord().ux);
			scl(blend(1.2, 0.25, d / 13., 2));
			ext(1.);
			face();

			if (d < 13)
				trunk(d + 1);
		endtk;
	}
	void branch(int d = 0)
	{
		real ang;
		begintk;
			ext(d == 0 ? 45 : 2.5);
			face();

			pushc();
			ang = rrnd(-8., 8.);
			loopi(5) {
				push();
				pit(ang);
				yaw(rrnd(0., 18.));
				scl(0.95);
				ext(1.);
				face();
			}
			if (d < 2.) {
				branch(d + 1.);
			}
			pop(5);
			popc();

			pushc();
			ang = rrnd(-8., 8.);
			loopi(6) {
				push();
				pit(ang);
				yaw(-rrnd(0., 18.));
				ext(1.);
				scl(0.925);
				face();
			}
			if (d < 3.) {
				branch(d + 1.);
			}
			pop(6);
			popc();

		endtk;
	}

	// -------------------------------------
	// tree
	// -------------------------------------
	void tree()
	{
		comv(true);
		color = rgb(rrnd(1, 200), 200, rrnd(1, 200));

		edge e;
		loopi(8) {
			real ang = __ai * PI2;
			real r = 2.0f;
			vec p = vec(cos(ang), 0, sin(ang)) * r;
			p.y *= blend2(1., 8., __ai, 2.);
			e = e | p;
		}

		begintke(e);
		branch();
		endtk
	}

	// -------------------------------------
	// lotus
	// -------------------------------------
	void trunk_lotus1(int len, int d)
	{
		begintk;
		rot(blend(-10, 10, d / real(len)), coord().ux);
		rot(blend(-10, 10, d / real(len)), coord().uy);
		scl(0.95);
		ext(1.);
		face();

		if (d < len)
			trunk_lotus1(len, d + 1);
		pop();
	}
	void trunk_lotus2(int len, real sz, int d)
	{
		begintk;
		rot(blend(-10, 10, d / 13.), coord().ux);
		scl(blend(1.5 * sz, 0.25, d / 13., 2));
		ext(1.);
		face();

		if (d < len)
			trunk_lotus2(len, sz, d + 1);
		endtk;
	}
	void lotus()
	{
		comv(true);

		pushc();
		int cdc = coordcur();
		loopj(4)
		{
			rotcoord(90, vec3::UY);
			coorddummy();
			color = rgb(50, 150, 0);
			{
				edge e;
				loopi(8) {
					real ang = __ai * PI2;
					real r = 1.0f;
					vec p = vec(cos(ang), 0, sin(ang)) * r;
					e = e | p;
				}
				push(e);
				trunk_lotus1(15 + 5 * j, 0);
				pop();
			}
			{
				edge e;
				loopi(8) {
					real ang = __ai * PI;
					real r = 1.0f;
					vec p = vec(cos(ang), 0, sin(ang)) * r;
					e = e | p;
				}

				color = rgb(240, 150, 250);
				loopi(8) {
					begintke(e);
					yaw(45 * i);
					trunk_lotus2(10 + j * 4, blend(0.8, 1.0, __aj), 0);

					endtk;
				}
			}
			popc(-cdc - 2);
		}
	}
	// -------------------------------------
	// shell
	// -------------------------------------
	void shell()
	{
		comv(true);
		color = rgb(rrnd(0, 150), rrnd(0, 150), rrnd(0, 150));

		edge e;
		loopi(32) {
			real ang = __ai * PI;
			real r = 12.0f;
			vec p = vec(cos(ang), 0, sin(ang)) * r;
			p.x *= blend(1., 2., __ai, 18);

			e = e | p;
		}

		begintke(e);
		trunk(0, 58,
			trunk_cb(d){
				rot(blend(10, 15, d / 58.), vec3::UX);
				mov(vec3::UX * blend(0.1, 0.05, d / 58.));
				scl(0.97);
				ext((d % 2 == 1 ? 1 : 0.25) * blend(1, 0.25, d / 158.) * 0.05);
				face();
			}
		);
		endtk;
	}
	void pipeshell()
	{
		comv(true);
		color = rgb(200, 200, 150);

		edge e;
		loopi(32) {
			real ang = __ai * PI2;
			real r = 12.0f;
			vec p = vec(cos(ang), 0, sin(ang)) * r;
			
			e = e | p;
		}

		begintke(e);
		trunk(0, 158,
			trunk_cb(d){
			//rot(blend(10, 15, d / 58.), vec3::UX);
			//mov(vec3::UX* blend(0.25, 0.15, d / 158.));

			rot(blend(-1, 1, noise(coord().o)), vec3::UX);
			scl(0.995);
			ext((d % 2 == 1 ? 1 : 0.25)* blend(1, 0.25, d / 158.) * 1);
			face(d % 2);
		}
		);
		endtk;
		//savesubmesh3DS("C:\\Users\\18858\\Documents\\LAB\\ZEXE\\shell.obj", SUBMESH);
	}
	void shiyan_upper()
	{
		comv(true);
		color = rgb(100, 80, 90);

		edge e;
		loopi(16) {
			real ang = __ai * PI / 2;
			real r = 5.0f;
			vec p = vec(
				0.5 * (cos(ang) + blend(2., 0., __ai, 0.5)), 
				0, 
				0.1 + sin(ang)) * r;

			e = e | p;
		}
		e = e | (e.mirrorcpy(vec::ZERO, vec::UZ).invertcpy());

		begintke(e);
		trunk(0, 158,
			trunk_cb(d){
			rot(blend(1, 5, d / 158.), vec3::UX);
			scl(0.97);
			ext((d % 2 == 1 ? 1 : 0.25)* blend(1, 0.25, d / 58.) * 0.05);
			face(2);
		}
		);
		endtk;
	}
	void shiyan_lower()
	{
		comv(true);
		color = rgb(80, 80, 70);

		edge e;
		loopi(16) {
			real ang = __ai * PI / 2;
			real r = 5.0f;
			vec p = vec(
				0.5 * (cos(ang) + blend(2., 0., __ai, 0.5)),
				0,
				0.1 + sin(ang)) * r;

			e = e | p;
		}
		e = e | (e.mirrorcpy(vec::ZERO, vec::UZ).invertcpy());
		//e.invert();

		begintke(e);
		trunk(0, 200,
			trunk_cb(d){
			rot(-blend(1, 1, d / 158.), vec3::UX);
			scl(0.97);
			ext((d % 2 == 1 ? 1 : 0.25)* blend(1, 0.25, d / 58.) * 0.05);

			face(1);
		}
		);
		endtk;
	}
}

// -------------------------------------
// test
// -------------------------------------
void test()
{
	if (luaparam[0] == 1)
	{
		nforms::shell();
	}
	else
	{
		nforms::tree();
	}

	//nforms::shiyan_upper();
	//nforms::shiyan_lower();
}
