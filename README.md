# Genode support for i.MX8MQ-based boards

This repository complements the Genode OS framework (https://genode.org) with
the board support needed to use Genode on devices based on i.MX 8MQ SoCs.

To use it, you first need to obtain a clone of Genode:

! git clone https://github.com/genodelabs/genode.git genode

Now, clone the _genode-imx8mq.git_ repository to _genode/repos/imx8mq_:

! git clone https://github.com/nfeske/genode-imx8mq.git genode/repos/imx8mq

For enabling the board support, adjust the build-directory configuration
_etc/build.conf_ by adding the following line before the other 'REPOSITORIES'
definitions so that the _imx8mq_ repository is prioritized over the others.

! REPOSITORIES += $(GENODE_DIR)/repos/imx8mq


License
-------

Genode-specific code is provided under Genode's regular open-source license,
which is AGPLv3 + open-source linking exception. This code is also available
under a commercial license offered by Genode Labs.

For code ported from other projects - e.g., device drivers ported from the
Linux kernel - the license of the originating upstream project applies.

Please refer to the individual file headers for detailed information.
