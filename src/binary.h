#pragma once

#include "types.h"
#include "variant.h"
#include "hashmap.h"

typedef uint64_t command;
#define EMPTY_CMD (command(-1))

enum CommandType
{
    COMMAND_OPCODE,
    COMMAND_ADDR,
    COMMAND_POS,
};

enum OpCodeType
{
    OPCODE_ASSIGN,

    OPCODE_PLUS,
    OPCODE_MINUS,
    OPCODE_MULTIPLY,
	OPCODE_DIVIDE,
	OPCODE_DIVIDE_MOD,

    OPCODE_PLUS_ASSIGN,
    OPCODE_MINUS_ASSIGN,
    OPCODE_MULTIPLY_ASSIGN,
	OPCODE_DIVIDE_ASSIGN,
	OPCODE_DIVIDE_MOD_ASSIGN,

	OPCODE_RETURN,
	
	OPCODE_JNE,
	OPCODE_JMP,
	
    OPCODE_AND,
    OPCODE_OR,
    OPCODE_LESS,
	OPCODE_MORE,
	OPCODE_EQUAL,
	OPCODE_MOREEQUAL,
	OPCODE_LESSEQUAL,
	OPCODE_NOTEQUAL,
	OPCODE_NOT,
	
    OPCODE_CALL,
    
    OPCODE_SLEEP,
    OPCODE_YIELD,
};

enum AddrType
{
	ADDR_STACK,
	ADDR_CONST,
	ADDR_CONTAINER,
};

struct container_addr
{
    command con;
    command key;
};

enum CallType
{
	CALL_NORMAL,
	CALL_FAKE,
};

#define MAKE_COMMAND(type, code) MAKEINT64(type, code)
#define MAKE_ADDR(addrtype, pos) MAKE_COMMAND(COMMAND_ADDR, MAKEINT32(addrtype, pos))
#define MAKE_OPCODE(op) MAKE_COMMAND(COMMAND_OPCODE, op)
#define MAKE_POS(pos) MAKE_COMMAND(COMMAND_POS, pos)

#define COMMAND_TYPE(cmd) HIINT32(cmd)
#define COMMAND_CODE(cmd) LOINT32(cmd)

#define ADDR_TYPE(code) HIINT16(code)
#define ADDR_POS(code) LOINT16(code)

const char * OpCodeStr(int opcode);

struct fake;
class codegen;
struct func_binary
{
    String dump() const;
    // ���ջ�ռ�
    int m_maxstack;
    // ��������
    int m_paramnum;
    // ����
    const char * m_name;
    // �ļ���
    const char * m_filename;
    // ����
    const char * m_packagename;
    // �����ƻ�����
    command * m_buff;
    int m_size;
    // �������кŻ�����
    int * m_lineno_buff;
    int m_lineno_size;
    // ����
    variant * m_const_list;
    int m_const_list_num;
    // container��ַ
    container_addr * m_container_addr_list;
    int m_container_addr_list_num;
    // ����
    int m_pos;
    // ռ�ñ��
    mutable int m_use;
    // ����
    mutable func_binary * m_backup;
};

#define FUNC_BINARY_INI(fb) \
	memset(&(fb), 0, sizeof(func_binary))

#define FUNC_BINARY_NAME(fb) \
	((fb).m_name)

#define FUNC_BINARY_FILENAME(fb) \
	((fb).m_filename)
	
#define FUNC_BINARY_PACKAGENAME(fb) \
	((fb).m_packagename)
	
#define FUNC_BINARY_CMDSIZE(fb) \
	((fb).m_size)

#define FUNC_BINARY_LINENO_SIZE(fb) \
	((fb).m_lineno_size)
	
#define FUNC_BINARY_SIZE(fb) \
	((fb).m_size * sizeof(command))

#define FUNC_BINARY_MAX_STACK(fb) \
	((fb).m_maxstack)

#define FUNC_BINARY_PARAMNUM(fb) \
	((fb).m_paramnum)
	
#define FUNC_BINARY_USE(fb) \
	((fb).m_use)
	
#define FUNC_BINARY_BACKUP(fb) \
	((fb).m_backup)
	
#define FUNC_BINARY_BACKUP_MOVE(fb) \
	{ \
		func_binary * tmp = (fb).m_backup; \
		(fb).m_backup = 0; \
		FUNC_BINARY_DELETE(fb); \
		memcpy((void *)&(fb), tmp, sizeof((fb))); \
		safe_fkfree(m_fk, tmp); \
	}

#define FUNC_BINARY_DELETE(fb) \
	safe_fkfree(m_fk, (fb).m_name); \
	safe_fkfree(m_fk, (fb).m_filename); \
	safe_fkfree(m_fk, (fb).m_packagename); \
	safe_fkfree(m_fk, (fb).m_buff); \
	safe_fkfree(m_fk, (fb).m_lineno_buff); \
	safe_fkfree(m_fk, (fb).m_const_list); \
	safe_fkfree(m_fk, (fb).m_container_addr_list); \
	if ((fb).m_backup) \
	{ \
		safe_fkfree(m_fk, (fb).m_backup->m_name); \
		safe_fkfree(m_fk, (fb).m_backup->m_filename); \
		safe_fkfree(m_fk, (fb).m_backup->m_packagename); \
		safe_fkfree(m_fk, (fb).m_backup->m_buff); \
		safe_fkfree(m_fk, (fb).m_backup->m_lineno_buff); \
		safe_fkfree(m_fk, (fb).m_backup->m_const_list); \
		safe_fkfree(m_fk, (fb).m_backup->m_container_addr_list); \
	} \
	safe_fkfree(m_fk, (fb).m_backup)

class binary
{
    friend class assembler;
public:
    force_inline binary(fake * fk) : m_fk(fk)
    {
    }

    force_inline ~binary()
    {
        clear();
    }

    force_inline fake * getfake()
    {
        return m_fk;
    }

    force_inline void clear()
    {
    	m_dump.clear();
    }

	bool add_func(const variant & name, const func_binary & bin);
    
    String & dump() const;
    String & dump(const char * func) const;
    
    void move();
    
private:
    fake * m_fk;   
    mutable String m_dump;
};

