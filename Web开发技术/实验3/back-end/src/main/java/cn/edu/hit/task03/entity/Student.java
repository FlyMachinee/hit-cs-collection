package cn.edu.hit.task03.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.sql.Date;

@Data
@NoArgsConstructor
@AllArgsConstructor
public class Student {
    private String sid;
    private String sname;
    private Boolean sgender;
    private Integer sgrade;
    private Date sbirthdate;
    private Integer sage;
}
