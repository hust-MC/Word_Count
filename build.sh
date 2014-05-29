# build.sh

rmmod word_count
make -C $KERNEL_PATH M=$MY_DEST
insmod $MY_DEST/word_count.ko
