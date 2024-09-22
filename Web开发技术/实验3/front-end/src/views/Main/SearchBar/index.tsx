import Search, { SearchProps } from "antd/es/input/Search";
import { useState } from "react";

interface SearchBarProps {
  onQuery: SearchProps["onSearch"];
}

const SearchBar = ({ onQuery }: SearchBarProps) => {
  const [queryName, setQueryName] = useState("");
  return (
    <Search
      value={queryName}
      placeholder="按姓名模糊查询（留空为全部）"
      allowClear
      enterButton="查询"
      size="large"
      onChange={(e) => setQueryName(e.target.value)}
      onSearch={onQuery}
      style={{ width: 400 }}
    />
  );
};

export default SearchBar;
