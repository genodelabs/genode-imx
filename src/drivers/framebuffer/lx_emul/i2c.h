/**
 * \brief  Lx_emul support to access I2C service
 * \author Stefan Kalkowski
 * \date   2021-05-17
 */

/*
 * Copyright (C) 2021 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#ifndef _LX_EMUL__I2C_H_
#define _LX_EMUL__I2C_H_

#ifdef __cplusplus
extern "C" {
#endif

unsigned char lx_emul_i2c_read_byte(unsigned char addr);
void          lx_emul_i2c_write_bytes(unsigned len, unsigned char * bytes);

#ifdef __cplusplus
}
#endif

#endif /* _LX_EMUL__I2C_H_ */
