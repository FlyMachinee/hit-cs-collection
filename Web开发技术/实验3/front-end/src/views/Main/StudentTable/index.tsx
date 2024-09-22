import React, { useEffect, useState } from "react";
import { Button, Popconfirm, Table } from "antd";
import type { PaginationProps, PopconfirmProps, TableProps } from "antd";
import axios from "axios";
import { ColumnsType } from "antd/es/table";
import StudentModal from "../StudentModal";
import { PlusOutlined } from "@ant-design/icons";

interface Student {
  sid: string;
  sname: string;
  sgender: boolean | null;
  sgrade: number | null;
  sbirthdate: Date | null;
  sage: number | null;
}

interface StudentModalProps {
  title: string;
  isOpen: boolean;
  onOk: (stu: Student) => void;
  initialStudent: Student | null;
}

interface StudentTableProps {
  queryName: string;
}

const StudentTable: React.FC<StudentTableProps> = ({
  queryName,
}: StudentTableProps) => {
  const [students, setStudents] = useState<Student[]>([]);
  const [loading, setLoading] = useState<boolean>(false);
  const [pagination, setPagination] = useState<PaginationProps>({
    current: 1,
    pageSize: 7,
    hideOnSinglePage: true,
  });
  const [studentModalProps, setStudentModalProps] = useState<StudentModalProps>(
    {
      title: "",
      isOpen: false,
      onOk: (stu) => {},
      initialStudent: null,
    }
  );

  const setIsOpen = (isOpen: boolean) => {
    setStudentModalProps({ ...studentModalProps, isOpen: isOpen });
  };

  useEffect(() => {
    const queryData = async (name: string): Promise<Student[]> => {
      const res = await axios.get("http://localhost:8080/hit/student/query", {
        params: { name },
      });

      return res.data;
    };

    const query = async (name: string) => {
      setLoading(true);
      const res = await queryData(name);
      setStudents(res);
      setLoading(false);
      setPagination((pagination: PaginationProps) => ({
        ...pagination,
        current: 1,
        total: res.length,
      }));
    };

    query(queryName);
  }, [queryName]);

  const handleTableChange: TableProps["onChange"] = (pagination) => {
    setPagination(pagination);
  };

  const columns: ColumnsType<Student> = [
    {
      title: "学号",
      dataIndex: "sid",
    },
    {
      title: "姓名",
      dataIndex: "sname",
    },
    {
      title: "性别",
      dataIndex: "sgender",
      render: (sgender) => (sgender === null ? "未知" : sgender ? "男" : "女"),
    },
    {
      title: "成绩",
      dataIndex: "sgrade",
      render: (data) =>
        data === null || data === "" ? (
          <span style={{ color: "silver" }}>
            <i>null</i>
          </span>
        ) : (
          <span style={{ color: data >= 60 ? "green" : "red" }}>{data}</span>
        ),
    },
    {
      title: "出生日期",
      dataIndex: "sbirthdate",
      render: (data) => {
        try {
          return data === null || data === undefined || data === "" ? (
            <span style={{ color: "silver" }}>
              <i>null</i>
            </span>
          ) : (
            data.format("YYYY-MM-DD")
          );
        } catch {
          return data;
        }
      },
    },
    {
      title: "年龄",
      dataIndex: "sage",
      render: (data) =>
        data === null || data === "" ? (
          <span style={{ color: "silver" }}>
            <i>null</i>
          </span>
        ) : (
          data
        ),
    },
    {
      title: "操作",
      key: "action",
      width: 110,
      render: (_, student) => {
        const onConfirm: PopconfirmProps["onConfirm"] = () => {
          axios.delete("http://localhost:8080/hit/student/remove", {
            params: { sid: student.sid },
          });
          setStudents(students.filter((stu) => stu.sid !== student.sid));
          setPagination((pagination: PaginationProps) => ({
            ...pagination,
            total:
              pagination.total === undefined ? undefined : pagination.total - 1,
          }));
        };

        const onModifyOk = (newStu: Student) => {
          axios.put("http://localhost:8080/hit/student/modify", newStu);
          setStudents(
            students.map((stu: Student) =>
              stu.sid === newStu.sid ? newStu : stu
            )
          );
        };

        return (
          <>
            <Button
              type="link"
              size="small"
              onClick={() => {
                setStudentModalProps({
                  ...studentModalProps,
                  title: "修改学生",
                  isOpen: true,
                  initialStudent: student,
                  onOk: onModifyOk,
                });
              }}
            >
              修改
            </Button>
            <Popconfirm
              title="删除学生"
              description="你确定要删除这个学生吗？"
              onConfirm={onConfirm}
              okText="是"
              cancelText="否"
            >
              <Button type="link" size="small" danger>
                删除
              </Button>
            </Popconfirm>
          </>
        );
      },
    },
  ];

  const onCreateOk = (stu: Student) => {
    axios.post("http://localhost:8080/hit/student/create", stu);
    setStudents(
      [...students, stu].sort((lhs, rhs) => lhs.sid.localeCompare(rhs.sid))
    );
    setPagination((pagination: PaginationProps) => ({
      ...pagination,
      total: pagination.total === undefined ? undefined : pagination.total + 1,
    }));
  };

  const onCreate = () => {
    setStudentModalProps({
      ...studentModalProps,
      title: "新建学生",
      isOpen: true,
      initialStudent: null,
      onOk: onCreateOk,
    });
  };

  return (
    <>
      <Button
        type="primary"
        icon={<PlusOutlined />}
        style={{ width: 130 }}
        onClick={onCreate}
      >
        新建学生
      </Button>
      <Table
        columns={columns}
        rowKey="sid"
        dataSource={students}
        pagination={pagination}
        loading={loading}
        onChange={handleTableChange}
        sticky={students.length > 0}
        scroll={{ x: "max-content" }}
        size="middle"
      />
      <StudentModal modalProps={studentModalProps} setIsOpen={setIsOpen} />
    </>
  );
};

export default StudentTable;
