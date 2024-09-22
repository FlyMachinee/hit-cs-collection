package cn.edu.hit.task03.mapper;

import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface UserMapper {
    @Select("select count(*) from users where username=#{username} and password=#{password}")
    Integer login(String username, String password);
}
