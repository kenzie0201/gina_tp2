################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
mylib/ADC.obj: ../mylib/ADC.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --include_path="/Users/wangeorgina/Documents/tp2/gina_tp2/hello" --include_path="/Applications/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="mylib/ADC.d" --obj_directory="mylib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mylib/digitpot.obj: ../mylib/digitpot.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --include_path="/Users/wangeorgina/Documents/tp2/gina_tp2/hello" --include_path="/Applications/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="mylib/digitpot.d" --obj_directory="mylib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mylib/display.obj: ../mylib/display.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --include_path="/Users/wangeorgina/Documents/tp2/gina_tp2/hello" --include_path="/Applications/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="mylib/display.d" --obj_directory="mylib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mylib/led.obj: ../mylib/led.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --include_path="/Users/wangeorgina/Documents/tp2/gina_tp2/hello" --include_path="/Applications/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="mylib/led.d" --obj_directory="mylib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mylib/mypwm.obj: ../mylib/mypwm.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --include_path="/Users/wangeorgina/Documents/tp2/gina_tp2/hello" --include_path="/Applications/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="mylib/mypwm.d" --obj_directory="mylib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mylib/switchgain.obj: ../mylib/switchgain.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --include_path="/Users/wangeorgina/Documents/tp2/gina_tp2/hello" --include_path="/Applications/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="mylib/switchgain.d" --obj_directory="mylib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

mylib/uart.obj: ../mylib/uart.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me -O2 --include_path="/Applications/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.1.LTS/include" --include_path="/Users/wangeorgina/Documents/tp2/gina_tp2/hello" --include_path="/Applications/ti/TivaWare_C_Series-2.1.4.178" --advice:power=all --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --ual --preproc_with_compile --preproc_dependency="mylib/uart.d" --obj_directory="mylib" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


