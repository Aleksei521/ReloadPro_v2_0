
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 05/25/2019 at 20:06
// Component: CoolerWarning_v1_0
module CoolerWarning_v1_0 (
	output  cooler_status,
	input   clk,
	input   cooler_in
);

//`#start body` -- edit after this line, do not edit this line
    localparam STATE_LOAD_PERIOD    = 2'b00;  //Загружаем период D0->A0
	localparam STATE_DEC_PERIOD     = 2'b01;  //декримен пероида A0--
	localparam STATE_CMP_Z_PERIOD   = 2'b10;  //Проверяем период на ноль, проверяем флаги переднего и заднего фронта
                                              //Также флаги подавления дребезга переднего и заднего фронта
    localparam STATE_LOAD_DELAY     =2'b11; //загружаем задержку на подавления дребезга

    reg  [1:0]state;  //Машина состояний
    reg r_cooler_status;
    reg r_rising_edge;
    reg r_rising_edge_bounce;
    reg r_falling_edge;
    wire z_period;
    wire period_eq_bounce;
    assign cooler_status=r_cooler_status;
    
	always @(posedge clk )
    case (state)
	    STATE_LOAD_PERIOD:  //
	    begin
            r_rising_edge<=1'b0;
            r_rising_edge_bounce<=1'b0;
            r_falling_edge<=1'b0;
            state <= STATE_DEC_PERIOD;
        end
	    STATE_DEC_PERIOD:  //
	    begin
            state <= STATE_CMP_Z_PERIOD;
        end
	    STATE_CMP_Z_PERIOD:  //
	    begin
            if(z_period)
            begin
                r_cooler_status<=1'b0;
                state<=STATE_LOAD_PERIOD;
            end
            else
            begin
                if(r_rising_edge)//Ранее уже был передний фронт
                begin
                    if(r_rising_edge_bounce)// Если флаг подавления дребезга переднего фронта установлен
                    begin
                        if(r_falling_edge)//проверяем установлен ли флаг заднего фронта
                        begin
                            if(period_eq_bounce)//Если флаг подавления дребезга не установлен, проверяем окончание периода подавления дребезга
                            begin
                                if(cooler_in)//Если период подавления дребезга окончен, проверяем входной сигнал
                                begin
                                    r_falling_edge<=1'b0;//если входной сигнал равен 1
                                    r_rising_edge_bounce<=1'b0;//То сбрасываем флаги
                                    r_rising_edge<=1'b0;
                                    state <= STATE_DEC_PERIOD;//и продолжаем отсчет
                                end
                                else
                                begin
                                    r_cooler_status<=1'b1;//Если входной сигнал равен 0 то устанавливаем статус в 1 
                                    state<=STATE_LOAD_PERIOD;
                                end
                            end
                            else
                            begin
                                state <= STATE_DEC_PERIOD;//и продолжаем отсчет
                            end
                        end
                        else
                        begin
                            if(~cooler_in)//Если входной сигнал равен нулю
                            begin
                                r_falling_edge<=1'b1;//Устанавливаем флаг заднего фронта
                                state<=STATE_LOAD_DELAY;//Загружаем в A1 время истечения задержки подавления дребезга
                            end
                            else
                            begin
                                state <= STATE_DEC_PERIOD;//и продолжаем отсчет
                            end
                        end
                    end
                    else
                    begin
                        if(period_eq_bounce)//Если флаг подавления дребезга не установлен, проверяем окончание периода подавления дребезга
                        begin
                            if(cooler_in)//Если период подавления дребезга окончен, проверяем входной сигнал
                            begin
                                r_rising_edge_bounce<=1'b1;//Если так же равен 1 то устанавливаем флаг подавления дребезга переднего фронта
                            end
                            else
                            begin
                                r_rising_edge<=1'b0;
                            end
                        end
                        state <= STATE_DEC_PERIOD;//и продолжаем отсчет
                    end
                end
                else
                begin
                    if(cooler_in)
                    begin
                        r_rising_edge<=1'b1;
                        state<=STATE_LOAD_DELAY;
                    end
                    else
                    begin
                        state <= STATE_DEC_PERIOD;//и продолжаем отсчет
                    end
                end
            end
        end
	    STATE_LOAD_DELAY:  //
	    begin
            state <= STATE_DEC_PERIOD;
        end
    endcase
//        Your code goes here

cy_psoc3_dp8 #(.cy_dpconfig_a(
{
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC___D0, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM0:    LOAD PERIOD D0->A0*/
    `CS_ALU_OP__DEC, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC__ALU, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM1:    DEC PERIOD A0--*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM2:    TEST STATES AND INPUT*/
    `CS_ALU_OP__SUB, `CS_SRCA_A0, `CS_SRCB_D1,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC__ALU,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM3:    LOAD A1*/
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM4:    */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM5:    */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM6:    */
    `CS_ALU_OP_PASS, `CS_SRCA_A0, `CS_SRCB_D0,
    `CS_SHFT_OP_PASS, `CS_A0_SRC_NONE, `CS_A1_SRC_NONE,
    `CS_FEEDBACK_DSBL, `CS_CI_SEL_CFGA, `CS_SI_SEL_CFGA,
    `CS_CMP_SEL_CFGA, /*CFGRAM7:    */
    8'hFF, 8'h00,  /*CFG9:    */
    8'hFF, 8'hFF,  /*CFG11-10:    */
    `SC_CMPB_A1_D1, `SC_CMPA_A1_A0, `SC_CI_B_ARITH,
    `SC_CI_A_ARITH, `SC_C1_MASK_DSBL, `SC_C0_MASK_DSBL,
    `SC_A_MASK_DSBL, `SC_DEF_SI_0, `SC_SI_B_DEFSI,
    `SC_SI_A_DEFSI, /*CFG13-12:    */
    `SC_A0_SRC_ACC, `SC_SHIFT_SL, 1'h0,
    1'h0, `SC_FIFO1_BUS, `SC_FIFO0_BUS,
    `SC_MSB_DSBL, `SC_MSB_BIT0, `SC_MSB_NOCHN,
    `SC_FB_NOCHN, `SC_CMP1_NOCHN,
    `SC_CMP0_NOCHN, /*CFG15-14:    */
    10'h00, `SC_FIFO_CLK__DP,`SC_FIFO_CAP_AX,
    `SC_FIFO_LEVEL,`SC_FIFO__SYNC,`SC_EXTCRC_DSBL,
    `SC_WRK16CAT_DSBL /*CFG17-16:    */
}
)) udb(
        /*  input                   */  .reset(1'b0),
        /*  input                   */  .clk(clk),
        /*  input   [02:00]         */  .cs_addr({1'b0,state}),
        /*  input                   */  .route_si(1'b0),
        /*  input                   */  .route_ci(1'b0),
        /*  input                   */  .f0_load(1'b0),
        /*  input                   */  .f1_load(1'b0),
        /*  input                   */  .d0_load(1'b0),
        /*  input                   */  .d1_load(1'b0),
        /*  output                  */  .ce0(),
        /*  output                  */  .cl0(),
        /*  output                  */  .z0(z_period),
        /*  output                  */  .ff0(),
        /*  output                  */  .ce1(period_eq_bounce),
        /*  output                  */  .cl1(),
        /*  output                  */  .z1(),
        /*  output                  */  .ff1(),
        /*  output                  */  .ov_msb(),
        /*  output                  */  .co_msb(),
        /*  output                  */  .cmsb(),
        /*  output                  */  .so(),
        /*  output                  */  .f0_bus_stat(),
        /*  output                  */  .f0_blk_stat(),
        /*  output                  */  .f1_bus_stat(),
        /*  output                  */  .f1_blk_stat()
);
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line




