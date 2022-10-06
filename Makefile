-include variables.mk

.PHONY: build
build: $(BUILD_DIR)/$(TARGET_LIB)

.PHONY: build_docker_image
build_docker_image:
	docker build . -t $(DOCKER_IMAGE)

.PHONY:
docker_build: build_docker_image
	docker run --rm -it \
		-u $$(id -u):$$(id -g) \
		-v $$PWD:/build/cvector \
		$(DOCKER_IMAGE)

$(BUILD_DIR)/$(TARGET_LIB): $(OBJS)
	$(AR) rcs $@ $(OBJS)

$(BUILD_DIR)/%.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(TEST_DIR)/%: $(TEST_DIR)/%.c $(BUILD_DIR)/$(TARGET_LIB)
	$(MKDIR_P) $(dir $@)
	$(CC) $(TEST_CFLAGS) $(TEST_LDFLAGS) $< $(BUILD_DIR)/$(TARGET_LIB) -o $@

.PHONY: test/%
test/%: $(BUILD_DIR)/$(TEST_DIR)/%_test
	$<

$(BUILD_DIR)/$(LIB_DIR)/%: $(LIB_DIR)/%
	$(MKDIR_P) $@
	BUILD_DIR=$(abspath $@) $(MAKE) -C $< build

.PHONY: compile_flags.txt
compile_flags.txt:
	echo $(CFLAGS) | tr ' ' '\n' > compile_flags.txt

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

