include $(GENODE_DIR)/repos/base-hw/recipes/src/base-hw_content.inc

content: src/bootstrap/board/imx8q_evk/board.h src/core/board/imx8q_evk/board.h

src/bootstrap/board/imx8q_evk/board.h:
	$(mirror_from_rep_dir)

src/core/board/imx8q_evk/board.h:
	$(mirror_from_rep_dir)
