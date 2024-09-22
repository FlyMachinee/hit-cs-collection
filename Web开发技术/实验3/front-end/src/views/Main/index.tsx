import React, { useState } from "react";
import { Flex, theme } from "antd";
import StudentTable from "./StudentTable";
import SearchBar from "./SearchBar";

const Main: React.FC = () => {
  const {
    token: { colorBgContainer, borderRadiusLG },
  } = theme.useToken();

  const [queryName, setQueryName] = useState("");

  return (
    <Flex
      style={{
        width: "100%",
        background: colorBgContainer,
        padding: 24,
        borderRadius: borderRadiusLG,
      }}
      gap="middle"
      justify="start"
      vertical
    >
      <SearchBar onQuery={(value) => setQueryName(value)} />
      <StudentTable queryName={queryName} />
    </Flex>
  );
};

export default Main;
