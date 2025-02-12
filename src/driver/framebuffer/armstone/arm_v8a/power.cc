
#include <lx_kit/env.h>

extern "C" void lx_emul_power_enable(const char *name);
extern "C" void lx_emul_power_disable(const char *name);

void lx_emul_power_enable(const char *name)
{
	using namespace Lx_kit;
	using namespace Genode;

	env().devices.for_each([&] (Device & d) {
		if (strcmp(d.compatible(), name) == 0) {
			error("Enable power domain ", name);
			d.enable();
		}
	});
}


void lx_emul_power_disable(const char *name)
{
	using namespace Lx_kit;
	using namespace Genode;

	env().devices.for_each([&] (Device & d) {
		if (strcmp(d.compatible(), name) == 0) {
			error("Disable power domain ", name);
			//d.disable();
		}
	});
}
