import React from "react";
import { Flex, Image, theme } from "antd";
import LoginForm from "@/views/Login/LoginForm/index";
import dropOutImage from "@/image/drop_out.jpg";

const Login: React.FC = () => {
  const {
    token: { colorBgContainer, borderRadiusLG },
  } = theme.useToken();
  return (
    <Flex
      style={{
        width: "100%",
        background: colorBgContainer,
        padding: 24,
        borderRadius: borderRadiusLG,
      }}
      gap="middle"
      justify="center"
      vertical
    >
      <Flex justify="space-evenly">
        <Image
          height={150}
          src={dropOutImage}
          title="退学通知书"
          alt="辅导员给你退学通知书啦！"
        />
        <LoginForm />
      </Flex>
    </Flex>
  );
};

export default Login;
