module comparator_tb;
  reg [31:0] A;
  reg [31:0] B;
  wire [31:0] F;

  wire eq = F[0];
  wire lt = F[1];
  wire u_lt = F[2];
  wire le = F[3];
  wire u_le = F[4];
  wire ne = F[5];
  wire ge = F[6];
  wire u_ge = F[7];
  wire gt = F[8];
  wire u_gt = F[9];

  // 实例化被测试模块
  comparator uut (
      .A(A),
      .B(B),
      .F(F)
  );

  initial begin
    // 测试相等
    A = 32'h00000010;
    B = 32'h00000010;
    $display("A = %h, B = %h, F = %b", A, B, F);
    #10;

    // 测试 A < B
    A = 32'h00000010;
    B = 32'h00000020;
    $display("A = %h, B = %h, F = %b", A, B, F);
    #10;

    // 测试 A > B
    A = 32'h00000020;
    B = 32'h00000010;
    $display("A = %h, B = %h, F = %b", A, B, F);
    #10;

    // 测试 A == B (负数)
    A = 32'hFFFFFFFF;
    B = 32'hFFFFFFFF;
    $display("A = %h, B = %h, F = %b", A, B, F);
    #10;

    // 测试 A < B (负数)
    A = 32'hFFFFFFFE;
    B = 32'hFFFFFFFF;
    $display("A = %h, B = %h, F = %b", A, B, F);
    #10;

    // 测试 A > B (负数)
    A = 32'hFFFFFFFF;
    B = 32'hFFFFFFFE;
    $display("A = %h, B = %h, F = %b", A, B, F);
    #10;

    // 结束仿真
    $finish;
  end
endmodule
