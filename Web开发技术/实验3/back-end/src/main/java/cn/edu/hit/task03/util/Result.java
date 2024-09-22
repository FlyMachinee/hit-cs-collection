package cn.edu.hit.task03.util;

public class Result {
    private Integer code;
    private String msg;

    private Result(Integer code, String msg) {
        this.code = code;
        this.msg = msg;
    }
    public static Result ok(String msg) {
        return new Result(200, msg);
    }
    public static Result failed(String msg) {
        return new Result(400, msg);
    }

    public Integer getCode() {
        return code;
    }

    public String getMsg() {
        return msg;
    }
}
