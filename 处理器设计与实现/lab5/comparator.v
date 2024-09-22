module comparator (
    input  wire [31:0] A,  // 左比较数
    input  wire [31:0] B,  // 右比较数
    output wire [31:0] F   // 比较结果向量
);
  wire signed [31:0] A_signed = A;
  wire signed [31:0] B_signed = B;

  wire eq = A == B;
  wire lt = A_signed < B_signed;
  wire u_lt = A < B;
  wire le = A_signed <= B_signed;
  wire u_le = A <= B;

  assign F = {
    22'b0,
    ~u_le,  // ~(无符号小于等于) => 无符号大于
    ~le,  // ~(无符号小于等于) => 有符号大于
    ~u_lt,  // ~(无符号小于) => 无符号大于等于
    ~lt,  // ~(有符号小于) => 有符号大于等于
    ~eq,  // ~(等于) => 不等于
    u_le,  // 无符号小于等于
    le,  // 有符号小于等于
    u_lt,  // 无符号小于
    lt,  // 有符号小于
    eq  // 等于
  };
endmodule
