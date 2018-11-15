//
//  "$Id: File.h 125715 2013-07-09 03:54:31Z sun_xiaohui $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef __INFRA3_FILE_H__
#define __INFRA3_FILE_H__

#include <string>
#ifdef _WIN32
#include <io.h>
#endif

#include "Defs.h"
#include "String.h"

namespace Dahua {
namespace Infra {


/// \struct FileInfo
/// \brief �ļ���Ϣ�ṹ
struct FileInfo
{
	enum {maxPathSize = 260};

	char		name[maxPathSize];	///< �ļ���
	uint16_t	attrib;			///< �ļ�����
	uint64_t	timeCreate;	///< �ļ�����ʱ��
	uint64_t	timeAccess;	///< �ļ�����ʱ��
	uint64_t	timeWrite;		///< �ļ��޸�ʱ��
	uint64_t	size;			///< �ļ���С
};


/// \struct io_vec
/// \brief io�����ṹ
struct io_vec
{
	void *iov_base;	///< ������ַָ�룬ָ�򻺳���
	size_t iov_len;	///< ָ������������
};

struct FileInternal;

/// \class CFile
/// \brief �ļ������װ
////////////////////////////////////////////////////////////////////////////////

class INFRA_API CFile
{
	CFile(CFile const&);
	CFile& operator=(CFile const&);

public:

	/// �ļ��򿪱�־
	enum OpenFlags {
		modeRead =         (int) 0x00000, ///< Ϊ����һ���ļ�������ļ������ڻ��޷��򿪣�Open����ʧ�ܡ�
		modeWrite =        (int) 0x00001, ///< Ϊд����һ�����ļ�������ļ����ڣ������ݽ������١�
		modeReadWrite =    (int) 0x00002, ///< Ϊ��д��һ���ļ�������ļ������ڻ��޷��򿪣�Open����ʧ�ܡ�
		shareCompat =      (int) 0x00000,
		shareExclusive =   (int) 0x00010,
		shareDenyWrite =   (int) 0x00020,
		shareDenyRead =    (int) 0x00030,
		shareDenyNone =    (int) 0x00040,
		modeNoInherit =    (int) 0x00080,
		modeCreate =       (int) 0x01000, ///< ����ļ������ڣ��Զ������ļ�����modeReadWrite���ʹ�á�
		modeNoTruncate =   (int) 0x02000, ///< ��modeCreateһ��ʹ�ã����Ҫ�������ļ��Ѿ����ڣ�ԭ�������ݱ�����
		typeText =         (int) 0x04000, // typeText and typeBinary are
		typeBinary =       (int) 0x08000, // used in derived classes only
		osNoBuffer =       (int) 0x10000, ///< �ϲ㴦���壬��ʱ��д��ƫ�ƺͳ��ȶ���Ҫ��ҳ���С���롣
		osWriteThrough =   (int) 0x20000,
		osRandomAccess =   (int) 0x40000,
		osSequentialScan = (int) 0x80000,
	};

	/// �ļ�����
	enum Attribute {
		// WIN32 ���ݵ��ļ��������루������ʹ�� posix ����������棩
		normal =    0x00,
		readOnly =  0x01,
		hidden =    0x02,
		system =    0x04,
		volume =    0x08,
		directory = 0x10,
		archive =   0x20,

		// posix ���ݵ��ļ���������
		posixFIFO		= 0x1000,
		posixCharacter	= 0x2000,	///< Character special (indicates a device if set)
		posixDirectory	= 0x4000,
		posixRegular	= 0x8000,

	};

	/// �ļ���λ�ο�λ��
	enum SeekPosition
	{
		begin = 0x0,
		current = 0x1,
		end = 0x2
	};

	/// �ļ����ʷ�ʽ
	enum AccessMode
	{
		accessExist = 0,
		accessWrite = 2,
		accessRead = 4,
		accessReadWrite = 6,
	};

	/// ���캯����
	CFile();

	/// ����������������ݻ��廹��Ч���ᱻ�ͷš�
	virtual ~CFile();

	/// ���ļ����򿪺��ļ�ָ��ƫ����0��������modeAppend��־�򿪵��ļ��ļ�ָ�����ļ�ĩβ��
	/// \param [in] pFileName �ļ�����
	/// \param [in] dwFlags �򿪱�־��Ĭ��ΪmodeReadWrite��
	/// \retval true  �򿪳ɹ�
	/// \retval false  ��ʧ�ܣ��ļ������ڻ��޷��򿪡�
	virtual bool open(const char* pFileName, uint32_t dwFlags = modeReadWrite);

	/// �ر��ļ���
	virtual void close();

	/// װ�����ݣ�������ļ�����һ����С�Ļ��壬���ļ����ݶ����û��壬���ػ���ָ�롣
	/// ��unload����һ���ṩ����
	/// \param [in] pFileName �ļ�����
	/// \retval NULL  װ��ʧ��
	/// \retval !NULL  ���ݻ���ָ�롣
	virtual uint8_t* load(const char* pFileName);

	/// �ͷ����ݻ���
	virtual void unload();

	/// ���ļ����ݡ����������ļ�ָ���Զ��ۼӡ�ʵ����Ȼ����size_t�������ɳ���size_t��ֵ��ʵ��
	/// \param [out] pBuffer ���ݻ����ָ�롣
	/// \param [in] dwCount Ҫ�������ֽ���
	/// \retval >=0  �������ֽ���
	/// \retval <0 ��ʧ��
	virtual int64_t read(void* pBuffer, int64_t dwCount);

	/// д�ļ����ݡ����������ļ�ָ���Զ��ۼӡ�ʵ����Ȼ����size_t�������ɳ���size_t��ֵ��ʵ��
	/// \param [in] pBuffer ���ݻ����ָ�롣
	/// \param [in] dwCount Ҫд����ֽ���
	/// \retval >=0  д����ֽ���
	/// \retval <0 дʧ��
	virtual int64_t write(void *pBuffer, int64_t dwCount);

	/// ͬ���ļ��ײ㻺�壬��д��������ã�ȷ��д��������Ѿ���������ϵͳ��
	virtual void flush();

	/// �ļ���λ��
	/// \param [in] lOff ƫ�������ֽ�Ϊ��λ��
	/// \param [in] nFrom ƫ�����λ�ã����õ���ƫ��ΪlOff+nFrom��
	/// \return ƫ�ƺ��ļ���ָ��λ�á�
	virtual int64_t seek(int64_t lOff, SeekPosition nFrom);

	/// ���ص�ǰ���ļ�ָ��λ��
	virtual int64_t getPosition();

	/// �����ļ�����
	virtual int64_t getLength();

	/// ���ı��ļ���ǰƫ�ƴ���ȡһ���ַ��������������ļ�ָ���Զ��ۼӡ�
	/// \param [out] s ���ݻ��塣
	/// \param [in] size ��Ҫ��ȡ���ַ�������
	/// \retval NULL  ��ȡʧ��
	/// \retval !NULL  �ַ���ָ�롣
	virtual char* gets(char* s, int64_t size);

	/// ���ı��ļ���ǰƫ�ƴ�д��һ���ַ�����д�������ļ�ָ���Զ��ۼӡ�
	/// \param [in] s ���ݻ��塣
	/// \return  ʵ��д���ַ������ȡ�
	virtual int64_t puts(const char* s);

	/// �ж��ļ��Ƿ��
	virtual bool isOpen();

	/// �ۺ�д�ļ�����
	/// \param iov �ۺ�������ַ
	/// \param iovcnt �ۺ�����Ԫ�ظ���
	/// \retval >=0  д����ֽ���
	/// \retval <0 дʧ��
	virtual int64_t writev(const struct io_vec *iov, int iovcnt);

	/// �������ļ�
	/// \param oldName �ɵ��ļ���
	/// \param oldName �µ��ļ���
	static bool rename(const char* oldName, const char* newName);

	/// ɾ���ļ�
	/// \param fileName �ļ���
	static bool remove(const char* fileName);

	/// ����Ŀ¼
	/// \param Ŀ¼��
	static bool makeDirectory(const char* dirName);

	/// ɾ��Ŀ¼
	/// \param Ŀ¼��
	static bool removeDirectory(const char* dirName);

	/// �ļ�ϵͳͳ��
	/// \param path ����·������һ���Ƿ�����Ŀ¼��
	/// \param userFreeBytes Ŀ¼�����ļ�ϵͳ��������û���ʣ��ռ��ֽ���
	/// \param totalBytes Ŀ¼�����ļ�ϵͳ�ܵ��ֽ���
	/// \param totalFreeBytes Ŀ¼�����ļ�ϵͳ�ܵ�ʣ��ռ��ֽ��������ʹ����Ӳ��
	///        �ռ���userFreeBytes���ܻ��totalFreeBytesС
	static bool statFS(const char* path,
		uint64_t& userFreeBytes,
		uint64_t& totalBytes,
		uint64_t& totalFreeBytes);

	/// �ж��ļ���Ŀ¼����Ȩ��
	/// \param path �ļ���Ŀ¼��·����
	/// \param mode ����Ȩ�ޣ�\see AccessMode
	/// \return �Ƿ���modeָ����Ȩ��
	static bool access(const char* path, int mode);

	/// ����·����ȡ�ļ���Ϣ
	/// \param path �ļ���Ŀ¼��·����
	/// \param info �ļ���Ϣ��\see FileInfo
	/// \return �Ƿ�ɹ�
	static bool stat(const char* path, FileInfo& info);

protected:

	FileInternal* m_internal;
};

/////////////////////////////////////////////////////////////////////////////
struct FileFindInternal;

/// \brief �ļ������֧࣬��'*','?'ͨ�������
class INFRA_API CFileFind
{
	CFileFind(CFileFind const&);
	CFileFind& operator=(CFileFind const&);

public:
	/// ���캯��
	CFileFind();

	/// ��������
	virtual ~CFileFind();

	/// ���ҵ�һ���ļ�
	/// \param fileName ����ͨ�����·����
	/// \return �Ƿ��ҵ��˵�һ���ļ�
	virtual bool findFile(const char* fileName);

	/// ������һ���ļ���ʹ�ú��ϴ�findFile��ͬ��������������findFile֮�����
	/// \return �Ƿ��ҵ�����һ���ļ�
	virtual bool findNextFile();

	/// �رղ��ң��رպ�����ٴε���findFile
	virtual void close();

	/// �õ����ҵ����ļ��ĳ���
	virtual int64_t getLength();

	/// �õ����ҵ����ļ����ļ���
	virtual CString getFileName();

	/// �õ����ҵ����ļ���ȫ·��
	virtual CString getFilePath();

	/// �Ƿ�Ϊֻ���ļ�
	virtual bool isReadOnly();

	/// �Ƿ�ΪĿ¼�ļ�
	virtual bool isDirectory();

	/// �Ƿ�Ϊ�����ļ�
	virtual bool isHidden();

	/// �Ƿ�Ϊ��ͨ�ļ�
	virtual bool isNormal();

protected:
	FileFindInternal* m_internal;
};

////////////////////////////////////////////////////////////////////////////////

/// �ļ�ϵͳ����������
class IFileSystem
{
public:
	typedef void* FileHandle;

	virtual ~IFileSystem() {}

	virtual FileHandle fopen(const char*, const char*) = 0;
	virtual int fclose(FileHandle) = 0;
	virtual int64_t fread(void*, int64_t, int64_t, FileHandle) = 0;
	virtual int64_t fwrite(const void*, int64_t, int64_t, FileHandle) = 0;
	virtual int fflush(FileHandle) = 0;
	virtual int fseek(FileHandle, int64_t, int) = 0;
	virtual int64_t ftell(FileHandle) = 0;
	virtual char* fgets(char*, int64_t, FileHandle) = 0;
	virtual int fputs(const char*, FileHandle) = 0;
	virtual int rename(const char* oldname, const char* newname) = 0;
	virtual int remove(const char* path) = 0;
	virtual int64_t findfirst(const char*, FileInfo&) = 0;
	virtual int findnext(int64_t, FileInfo&) = 0;
	virtual int findclose(int64_t) = 0;
	virtual int mkdir( const char* dirname) = 0;
	virtual int rmdir( const char* dirname) = 0;
	virtual int statfs( const char* path, uint64_t& userFreeBytes, uint64_t& totalBytes, uint64_t& totalFreeBytes) = 0;
	virtual int access( const char* path, int mode) = 0;
	virtual int stat( const char* path, FileInfo&) = 0;
	virtual size_t writev(int fileds, const struct io_vec *iov, int iovcnt) = 0;
};

/// Ϊ�˼����������ں��ļ�ϵͳ��֧�����ù��ӽӿڣ�ͨ����װ��ģ��ʵ����Щ�ӿڡ�
/// \param path ƥ���·��
/// \param filesystem �ļ�ϵͳ�ļ�����������ȡ������֮ǰ����������ܱ����٣�
///		Ϊ NULL ��ʾȡ������
void INFRA_API hookFileSystem(const char* path, IFileSystem* filesystem);


} // namespace Infra
} // namespace Dahua

#endif //__INFRA_FILE_H__

