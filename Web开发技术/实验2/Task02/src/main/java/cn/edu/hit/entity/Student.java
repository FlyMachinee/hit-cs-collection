package cn.edu.hit.entity;

import java.sql.Date;

public class Student {
    private String sid;
    private String sname;
    private Boolean sgender;
    private Integer sgrade;
    private Date sbirthdate;
    private Integer sage;

    public Student() {

    }
    public Student(String sid, String sname, Boolean sgender, Integer sgrade, Date sbirthdate, Integer sage) {
        this.sid = sid;
        this.sname = sname;
        this.sgender = sgender;
        this.sgrade = sgrade;
        this.sage = sage;
        this.sbirthdate = sbirthdate;
    }

    public String getSid() {
        return sid;
    }

    public void setSid(String sid) {
        this.sid = sid;
    }

    public String getSname() {
        return sname;
    }

    public void setSname(String sname) {
        this.sname = sname;
    }

    public Boolean getSgender() {
        return sgender;
    }

    public void setSgender(Boolean sgender) {
        this.sgender = sgender;
    }

    public Integer getSgrade() {
        return sgrade;
    }

    public void setSgrade(Integer sgrade) {
        this.sgrade = sgrade;
    }

    public Integer getSage() {
        return sage;
    }

    public void setSage(Integer sage) {
        this.sage = sage;
    }

    public Date getSbirthdate() {
        return sbirthdate;
    }

    public void setSbirthdate(Date sbirthdate) {
        this.sbirthdate = sbirthdate;
    }
}
