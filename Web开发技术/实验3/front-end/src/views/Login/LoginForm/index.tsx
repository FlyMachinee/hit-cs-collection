import { Form, Input, Checkbox, Button, type FormProps, message } from "antd";
import { useNavigate } from "react-router-dom";
import axios from "axios";

import { CurrentUserDispatchContext } from "@/context/userContext";
import { useContext } from "react";

type FieldType = {
  username: string;
  password: string;
  remember: string;
};

const LoginForm = () => {
  const [messageApi, contextHolder] = message.useMessage();
  const navigate = useNavigate();
  const currentUserDispatch = useContext(CurrentUserDispatchContext);

  const login = async (
    username: string,
    password: string
  ): Promise<{ code: number; msg: string }> => {
    const res = await axios.post("http://localhost:8080/hit/user/login", {
      username,
      password,
    });
    // console.log(res.data);
    return res.data;
  };

  const onFinish: FormProps<FieldType>["onFinish"] = async (
    values: FieldType
  ) => {
    const res = await login(values.username, values.password);
    if (res.code === 200) {
      sessionStorage.setItem("username", values.username);
      currentUserDispatch({
        type: "login",
        username: values.username,
      });
      navigate("/main");
    } else {
      messageApi.open({
        type: "error",
        content: res.msg,
      });
    }
  };

  return (
    <>
      {contextHolder}
      <Form
        name="basic"
        labelCol={{ span: 8 }}
        wrapperCol={{ span: 16 }}
        style={{ maxWidth: 600 }}
        initialValues={{ remember: true }}
        onFinish={onFinish}
        autoComplete="off"
      >
        <Form.Item<FieldType>
          label="用户名"
          name="username"
          rules={[{ required: true, message: "请输入用户名！" }]}
        >
          <Input />
        </Form.Item>

        <Form.Item<FieldType>
          label="密码"
          name="password"
          rules={[{ required: true, message: "请输入密码！" }]}
        >
          <Input.Password />
        </Form.Item>

        <Form.Item<FieldType>
          name="remember"
          valuePropName="checked"
          wrapperCol={{ offset: 8, span: 16 }}
        >
          <Checkbox>记住我</Checkbox>
        </Form.Item>

        <Form.Item wrapperCol={{ offset: 8, span: 16 }}>
          <Button type="primary" htmlType="submit">
            登陆
          </Button>
        </Form.Item>
      </Form>
    </>
  );
};

export default LoginForm;
