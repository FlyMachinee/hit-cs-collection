$(document).ready(function () {
    $.ajaxSettings.async = false
    $("#new-row-editer").hide()
    $("#username-span").append(sessionStorage.getItem("username"))
})
function onExit() {
    sessionStorage.setItem("username", null)
    return true;
}

function query_name_onChange() {
    let qname = $("#query-name").val()
    $.post(
        "student-servlet",
        {
            type: "selectBySname",
            qname: qname
        }
    )
    window.location.reload()
}
function modify_students_by_template_row(template_row, type) {

    let sid = template_row.find("input[name='sid']").val()
    let sname = template_row.find("input[name='sname']").val()
    let sgender = template_row.find("input.form-check-input:checked").val()
    let sgrade = template_row.find("input[name='sgrade']").val()
    let sbirthdate = template_row.find("input[name='sbirthdate']").val()
    let sage = template_row.find("input[name='sage']").val()

    if (!sid || !sname) {
        return {
            status: false,
            message: "学号和姓名不能为空！"
        }
    } else {
        let b = true;
        $.post(
            "student-servlet",
            {
                type,
                sid,
                sname,
                sgender,
                sgrade,
                sbirthdate,
                sage
            },
            function (message) {
                if (message.insertStatus === false) {
                    b = false
                }
            }
        )
        if (b)
            return {
                status: true
            }
        else
            return {
                status: false,
                message: "学号为 " + sid + " 的学生已经存在！"
            }
    }
}
function add_new_row_onClick() {
    let newRowAdder = $("#add-new-row")
    newRowAdder.hide()

    let newRow = $("<tr></tr>").html(update_or_insert_template_row("new"))
    newRow.attr("id", "data-new")
    let btnSubmit = newRow.find("button[name='button-submit']")
    let btnCancel = newRow.find("button[name='button-cancel']")

    btnSubmit.click(function () {
        let res = modify_students_by_template_row(newRow, "insert");

        if (res.status === true) {
            window.location.reload()
        }
        else {
            window.alert(res.message)
        }
    })

    btnCancel.click(function () {
        newRow.remove()
        newRowAdder.show()
    })

    newRowAdder.before(newRow);
}
function student_live_or_die(rowNum) {
    let thisRow = $("#data-" + rowNum);
    let sid = thisRow.children("td").eq(1).text()

    let sgrade = parseInt(thisRow.children("td").eq(4).text())
    let altered_sgrade = (sgrade < 60 ? 60 : 59);
    $.post(
        "student-servlet",
        {
            type: "update",
            sid,
            sgrade: altered_sgrade
        }
    )
    data_row_changer(
        thisRow,
        null,
        null,
        null,
        altered_sgrade.toString(),
        null,
        null
    )
}
function student_delete (rowNum) {
    let thisRow = $("#data-" + rowNum);
    let sid = thisRow.children("td").eq(1).text()
    let sname = thisRow.children("td").eq(2).text()

    if (confirm("确定要踢出学号为：" + sid + "，姓名为：" + sname + "的学生吗？")) {
        $.post(
            "student-servlet",
            {
                type: "delete",
                sid
            },
            function () {
                window.location.reload()
            }
        )
    }
}
function student_update_start(rowNum) {
    let thisRow = $("#data-" + rowNum);
    thisRow.hide()

    let origin_sid_text = thisRow.children("td").eq(1).text()
    let origin_sname_text = thisRow.children("td").eq(2).text()
    let origin_sgender_text = thisRow.children("td").eq(3).text()
    let origin_sgrade_text = thisRow.children("td").eq(4).text()
    let origin_sbirthdate_text = thisRow.children("td").eq(5).text()
    let origin_sage_text = thisRow.children("td").eq(6).text()

    let newRow = $("<tr></tr>").html(update_or_insert_template_row(rowNum.toString()))
    newRow.attr("id", "data-alter-" + rowNum)
    let btnSubmit = newRow.find("button[name='button-submit']")
    let btnCancel = newRow.find("button[name='button-cancel']")

    newRow.find("input[name='sid']").val(origin_sid_text)
    newRow.find("input[name='sid']").attr("disabled", true)

    newRow.find("input[name='sname']").val(origin_sname_text)

    if (origin_sgender_text === "男")
        newRow.find("input.form-check-input[value='true']").attr("checked", true)
    else if (origin_sgender_text === "女")
        newRow.find("input.form-check-input[value='false']").attr("checked", true)
    else
        newRow.find("input.form-check-input[value='undefined']").attr("checked", true)

    if (origin_sgrade_text !== "null")
        newRow.find("input[name='sgrade']").val(parseInt(origin_sgrade_text))

    newRow.find("input[name='sbirthdate']").val(origin_sbirthdate_text)

    if (origin_sage_text !== "null")
        newRow.find("input[name='sage']").val(parseInt(origin_sage_text))

    btnSubmit.click(function () {
        let res = modify_students_by_template_row(newRow, "update");

        if (res.status === true) {
            data_row_changer(
                thisRow,
                null,
                newRow.find("input[name='sname']").val(),
                newRow.find("input.form-check-input:checked").val(),
                newRow.find("input[name='sgrade']").val(),
                newRow.find("input[name='sbirthdate']").val(),
                newRow.find("input[name='sage']").val()
            )
            newRow.remove()
            thisRow.show()
        }
        else {
            window.alert(res.message)
        }
    })

    btnCancel.click(function () {
        newRow.remove()
        thisRow.show()
    })

    thisRow.after(newRow)
}

function update_or_insert_template_row(str) {
    return "<td>\n    <button type=\"button\" name=\"button-submit\">确认</button>\n    <br>\n    <button type=\"button\" name=\"button-cancel\">取消</button>\n  </td>\n  <td><input type=\"text\" name=\"sid\" placeholder=\"学号\" style=\"width: 100px\"></td>\n  <td><input type=\"text\" name=\"sname\" placeholder=\"姓名\" style=\"width: 100px\"></td>\n  <td>\n    <div class=\"form-check\">\n      <input class=\"form-check-input\" type=\"radio\" name=\"sgender-" + str + "\" value=\"true\">\n      <label class=\"form-check-label\" for=\"sgender-radio-1\">男</label>\n    </div>\n    <div class=\"form-check\">\n      <input class=\"form-check-input\" type=\"radio\" name=\"sgender-" + str + "\" value=\"false\">\n      <label class=\"form-check-label\" for=\"sgender-radio-2\">女</label>\n    </div>\n    <div class=\"form-check\">\n      <input class=\"form-check-input\" type=\"radio\" name=\"sgender-" + str + "\" value=\"undefined\" checked=\"checked\">\n      <label class=\"form-check-label\" for=\"sgender-radio-3\">未知</label>\n    </div>\n  </td>\n  <td><input type=\"number\" name=\"sgrade\" placeholder=\"成绩\" title='0-100的整数' max=\"100\" min=\"0\" step=\"1\" style=\"width: 55px\" oninput=\"if(!/^[0-9]+$/.test(value)) value=value.replace(/\\D/g,'');value=value.replace(/^(?:0+(?=[1-9])|0+(?=0$))/mg, '');if(value>100)value=100;if(value<0)value=null\"></td>\n  <td><input type=\"date\" name=\"sbirthdate\" placeholder=\"出生日期\" style=\"width: 120px\"></td>\n  <td><input type=\"text\" name=\"sage\" placeholder=\"年龄\" title='非负整数' min=\"0\" step=\"1\" pattern='^(0|[1-9][0-9]*)$' style=\"width: 55px\" oninput=\"if(!/^[0-9]+$/.test(value)) value=value.replace(/\\D/g,'');value=value.replace(/^(?:0+(?=[1-9])|0+(?=0$))/mg,'');if(value<0)value=null\"></td>"
}

function data_row_changer(data_row, sid_text, sname_text, sgender_text, sgrade_text, sbirthdate_text, sage_text) {
    if (sid_text !== null) {
        let sid_obj = $(data_row.children("td").eq(1))
        sid_obj.text(sid_text)
    }

    if (sname_text !== null) {
        let sname_obj = $(data_row.children("td").eq(2))
        sname_obj.text(sname_text)
    }

    if (sgender_text !== null) {
        let sgender_obj = $(data_row.children("td").eq(3))
        if (sgender_text === "undefined") {
            sgender_obj.css("color", "grey")
            sgender_obj.text("未知")
        } else {
            sgender_obj.css("color", "black")
            sgender_obj.text((sgender_text === "true") ? "男" : "女")
        }
    }

    if (sgrade_text !== null) {
        let sgrade_obj = $(data_row.children("td").eq(4))
        let judge_btn = $(data_row.find("button[name=judge-button]"))
        if (sgrade_text === "") {
            sgrade_obj.css("color", "grey")
            sgrade_obj.text("null")
            judge_btn.css("visibility", "hidden")
        } else {
            sgrade_obj.text(sgrade_text)
            judge_btn.css("visibility", "visible")
            if (parseInt(sgrade_text) < 60) {
                sgrade_obj.css("color", "red")
                judge_btn.text("大发慈悲，捞！")
            }
            else {
                sgrade_obj.css("color", "green")
                judge_btn.text("考这么高？挂！")
            }
        }
    }

    if (sbirthdate_text !== null) {
        let sbirthdate_obj = $(data_row.children("td").eq(5))
        if (sbirthdate_text === "") {
            sbirthdate_obj.text("null")
            sbirthdate_obj.css("color", "grey")
        }
        else {
            sbirthdate_obj.text(sbirthdate_text)
            sbirthdate_obj.css("color", "black")
        }
    }

    if (sage_text !== null) {
        let sage_obj = $(data_row.children("td").eq(6))
        if (sage_text === "") {
            sage_obj.text("null")
            sage_obj.css("color", "grey")
        }
        else {
            sage_obj.text(sage_text)
            sage_obj.css("color", "black")
        }
    }
}