import {
  DatePicker,
  Form,
  Input,
  InputNumber,
  Modal,
  Radio,
  type FormProps,
} from "antd";
import dayjs from "dayjs";

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

interface StudentModalPropsExtend {
  modalProps: StudentModalProps;
  setIsOpen: (isOpen: boolean) => void;
}

const StudentModal: React.FC<StudentModalPropsExtend> = ({
  modalProps,
  setIsOpen,
}: StudentModalPropsExtend) => {
  const { title, isOpen, onOk, initialStudent } = modalProps;
  const isCreateMethod = initialStudent === null;
  const isModifyMethod = !isCreateMethod;

  const onFinish: FormProps<Student>["onFinish"] = (stu) => {
    onOk(stu);
    setIsOpen(false);
  };

  return (
    <Modal
      title={title}
      open={isOpen}
      okButtonProps={{ htmlType: "submit", form: "basic" }}
      onCancel={() => setIsOpen(false)}
      okText={isCreateMethod ? "添加" : "保存"}
      cancelText="取消"
      destroyOnClose
    >
      <Form
        name="basic"
        onFinish={onFinish}
        autoComplete="off"
        style={{ padding: 20 }}
      >
        <Form.Item<Student>
          label="学号"
          name="sid"
          rules={[{ required: true, message: "学号不能为空！" }]}
          initialValue={isCreateMethod ? "" : initialStudent.sid}
        >
          <Input disabled={isModifyMethod} />
        </Form.Item>

        <Form.Item<Student>
          label="姓名"
          name="sname"
          rules={[{ required: true, message: "姓名不能为空！" }]}
          initialValue={isCreateMethod ? "" : initialStudent.sname}
        >
          <Input />
        </Form.Item>

        <Form.Item<Student>
          label="性别"
          name="sgender"
          initialValue={isCreateMethod ? null : initialStudent.sgender}
        >
          <Radio.Group>
            <Radio value={true}>男</Radio>
            <Radio value={false}>女</Radio>
            <Radio value={null}>未知</Radio>
          </Radio.Group>
        </Form.Item>

        <Form.Item<Student>
          label="成绩"
          name="sgrade"
          initialValue={isCreateMethod ? "" : initialStudent.sgrade}
        >
          <InputNumber min={0} max={100} />
        </Form.Item>

        {isCreateMethod || initialStudent?.sbirthdate === null ? (
          <Form.Item<Student> label="出生日期" name="sbirthdate">
            <DatePicker format="YYYY-MM-DD" />
          </Form.Item>
        ) : (
          <Form.Item<Student>
            label="出生日期"
            name="sbirthdate"
            initialValue={dayjs(initialStudent.sbirthdate, "YYYY-MM-DD")}
          >
            <DatePicker format="YYYY-MM-DD" />
          </Form.Item>
        )}

        <Form.Item<Student>
          label="年龄"
          name="sage"
          initialValue={isCreateMethod ? "" : initialStudent.sage}
        >
          <InputNumber min={0} />
        </Form.Item>
      </Form>
    </Modal>
  );
};

export default StudentModal;
