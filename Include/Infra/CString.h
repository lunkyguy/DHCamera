#ifndef __DAHUA_INFRA_CSTRING_H__
#define __DAHUA_INFRA_CSTRING_H__

#include <stddef.h> /// for size_t
#include <Infra/Defs.h>

namespace Dahua{
namespace Infra{

/// �ַ���������
class INFRA_API CString
{
public:
	/// �ַ���β����
	static const size_t npos;
	
	/// Ĭ�Ϲ��캯��
	CString();
		
	/// ���캯��
	/// \param str ���������ṩ��CString
	CString( CString const& str );
		
	/// ���캯��
	/// \param str �������ԭʼ�ַ���
	/// \param pos ��һ�������ַ���ԭ�ַ����е�ƫ��λ��
	/// \param len �����ַ�������
	CString( CString const& str, size_t pos, size_t len );
		
	/// ���캯��
	/// \param s �����ַ���
	CString( const char* s );

	/// ���캯��
	/// \param s �������ַ���
	/// \param n �����ַ�������
	CString( const char* s, size_t n );
		
	/// ���캯��
	/// \param c ����Ԫ�ַ�
	/// \param n ����Ԫ�ַ�������
	CString( char c, size_t n );
		
	/// ��������
	~CString();
		
	/// ��ֵ���캯��
	/// \param str ��ֵ�ַ���
	CString& operator=( CString const& str );
		
	/// ��ֵ���캯��
	/// \param str ��ֵ�ַ���
	CString& operator=( const char* str );
		
	/// ��ֵ���캯��
	/// \param c ʹ���ַ����쳤��Ϊ1���ַ���
	CString& operator=( char c );
		
	/// ��ȡ�ַ�������
	size_t size() const;
		
	/// ��ȡ�ַ�������
	size_t length() const;
		
	/// �����ַ�������
	/// \param n ���ú��ַ�������
	void resize( size_t n );
		
	/// ʹ��ָ���ַ������ַ�������
	/// \param c ָ���ַ���
	/// \param n ���ú��ַ�������
	void resize( char c, size_t n );
		
	/// �����ַ���ռ���ڴ��С
	size_t capacity() const;
		
	/// �����ַ����Ĵ洢����
	/// \param n �ַ��洢����
	void reserve( size_t n );
		
	/// ����ַ�������
	void clear();
		
	/// �ж��ַ�����Ϊ��
	bool empty() const;
		
	/// ��ȡ�ַ�����ָ�������ַ�
	/// \param pos ����ֵ
	char const& operator[]( size_t pos ) const;
		
	/// ��ȡ�ַ�����ָ�������ַ�
	/// \param pos ����ֵ
	char& operator[]( size_t pos );
		
	/// ��ȡ�ַ�����ָ�������ַ�
	/// \param n ����ֵ
	char const& at( size_t n ) const;
		
	/// ��ȡ�ַ�����ָ�������ַ�
	/// \param n ����ֵ
	char& at( size_t n );
		
	/// �����ԼӲ�����
	/// \param str ��׷���ַ���
	CString& operator+=( CString const& str );
		
	/// �����ԼӲ�����
	/// \param str ��׷���ַ���
	CString& operator+=( const char* str );
		
	/// �����ԼӲ�����
	/// \param c ��׷���ַ�
	CString& operator+=( const char c );
		
	/// ׷���ַ���
	/// \param str ׷�ӵ��ַ���
	CString& append( CString const& str );
		
	/// ׷��ָ�������ַ���
	/// \param str ׷�ӵ��ַ���
	/// \param pos ׷���ַ�����ƫ����
	/// \param n ׷���ַ�����
	CString& append( CString const& str, size_t pos, size_t n );
		
	/// ׷��ָ�����ȵ��ַ���
	/// \param s ׷���ַ�����ַ
	/// \param n ׷���ַ�������
	CString& append( const char* s, size_t n );
		
	/// ׷��ָ���ַ���
	/// \param s ׷���ַ�����ַ
	CString& append( const char* s );
		
	/// �����Զ��ַ�
	/// \param c ׷���ַ�
	void push_back( const char c );
		
	/// �������ַ������������
	/// \param str �����ַ���
	CString& assign( CString const& str );
		
	/// \ָ�������ַ�������
	/// \param str ԭʼ�������ַ���
	/// \param pos �����ַ���ƫ����
	/// \param n �����ַ�������
	CString& assign( CString const& str, size_t pos, size_t n );
		
	/// ʹ���ַ�����ַ�����ַ���
	/// \param s �ַ�����ַ
	/// \param n �ַ�����
	CString& assign( const char* s, size_t n );
		
	/// ��ָ����ַ�����ַ���
	/// \param s �����ַ�����ַ
	CString& assign( const char* s );
		
	/// ��ָ��λ�ò���ָ���ַ���
	/// \param pos ����λ��ƫ����
	/// \param str �����ַ���
	CString& insert( size_t pos, CString const& str );
		
	/// ��ָ��λ�ò���ָ�����ȵ��ַ���
	/// \param pos ����λ��ƫ����
	/// \param str ԭ�����ַ���
	/// \param pos �����ַ�������ԭ�����ַ�����ƫ����
	/// \param n �����ַ����ĳ���
	CString& insert( size_t pos1, CString const& str, 
		size_t pos2, size_t n );
		
	/// ��ָ��λ�ò���ָ���ַ���
	/// \param pos ����λ��ƫ����
	/// \param s �����ַ�����ַ
	/// \param n �����ַ�������
	CString& insert( size_t pos, const char* s, size_t n );
		
	/// ��ָ��λ�ò���ָ���ַ���
	/// \param pos ����λ��ƫ����
	/// \param s �����ַ�����ַ
	CString& insert( size_t pos, const char* s );
		
	/// ��ָ��λ�ò���n��ָ��Ԫ�ַ�
	/// \param pos ����λ��ƫ����
	/// \param c Ԫ�ַ�
	/// \param n Ԫ�ַ�����
	CString& insert( size_t pos, char c, size_t n );
		
	/// ��ָ��λ�ò���Ԫ�ַ�
	/// \param pos ����λ��ƫ����
	/// \param c Ԫ�ַ�
	CString& insert( size_t pos, char c );
		
	/// ��ָ��λ��ɾ��n���ַ�
	/// \param pos ɾ����ʼλ��ƫ����
	/// \param n ɾ���ַ�����
	CString& erase( size_t pos, size_t n );
		
	/// ��ָ��λ�õ�n���ַ��滻Ϊ��һ�ַ���
	/// \param pos �滻λ�õ�ƫ����
	/// \param n �滻�ַ�����
	/// \param str �滻�ַ���
	CString& replace( size_t pos, size_t n, CString const& str );
		
	/// ��ָ��λ�õ�n���ַ��滻Ϊ��һ�ַ���
	/// \param pos1 �滻λ�õ�ƫ����
	/// \param n1 �滻�ַ�����
	/// \param str �����滻��ԭʼ�ַ���
	/// \param pos2 �滻�ַ�����str�е�ƫ����
	CString& replace( size_t pos1, size_t n, 
		CString const& str, size_t pos2 );
			
	/// ��ָ��λ�õ�n���ַ��滻Ϊ��һ�ַ���
	/// \param pos1 �滻λ�õ�ƫ����
	/// \param n1 �滻�ַ�����
	/// \param s �滻�ַ�����ַ
	CString& replace( size_t pos1, size_t n1, const char* s );
		
	/// ��ָ��λ�ÿ���n���ַ�����ָ����ַ
	/// \param s[ out ] �����ַ�����ַ
	/// \param n[ int ] �����ַ�������
	/// \param pos[ int ] ������ʼλ��ƫ����
	size_t copy( char* s, size_t n, size_t pos = 0 ) const;
		
	/// ���������ַ���
	/// \param other �������ַ���
	void swap( CString& other );
		
	/// ��ȡ�ַ�������ʼָ��
	const char* c_str() const;
		
	/// ��ȡ�ַ�������ʼָ��
	const char* data() const;
		
	/// ����ָ���ַ���
	/// \param str ��ѯ�ַ���
	/// \param pos ��ѯ��ʼλ�õ�ƫ����
	/// \return ��ѯ�ɹ��������ַ�������λ�ã���ѯʧ�ܷ���npos
	size_t find( CString const& str, size_t pos = 0 ) const;
		
	/// ����ָ���ַ���
	/// \param s ��ѯ�ַ�����ַ
	/// \param pos ��ѯ��ʼλ�õ�ƫ����
	/// \param n ָ����ѯ���ĳ���
	/// \return ��ѯ�ɹ��������ַ�������λ�ã���ѯʧ�ܷ���npos
	size_t find( const char* s, size_t pos, size_t n ) const;
		
	/// ����ָ���ַ���
	/// \param s ��ѯ�ַ�����ַ
	/// \param pos ��ѯ��ʼλ�õ�ƫ����
	/// \return ��ѯ�ɹ��������ַ�������λ�ã���ѯʧ�ܷ���npos
	size_t find( const char* s, size_t pos = 0 ) const;
		
	/// ��ѯָ���ַ�
	/// \param s ��ѯ�ַ�
	/// \param pos ��ѯ��ʼλ�õ�ƫ����
	/// \��ѯ�ɹ��������ַ�������λ�ã���ѯʧ�ܷ���npos
	size_t find( char c, size_t pos = 0 ) const;
		
	/// �����ѯָ���ַ���
	/// \param str ��ѯ�ַ���
	/// \param pos ��ѯ��ʼλ�õ�ƫ����
	/// \return ��ѯ�ɹ��������ַ�������λ�ã���ѯʧ�ܷ���npos
	size_t rfind( CString const& str, size_t pos = npos ) const;
		
	/// �������ָ���ַ���
	/// \param s ��ѯ�ַ�����ַ
	/// \param pos ��ѯ��ʼλ�õ�ƫ����
	/// \param n ָ����ѯ���ĳ���
	/// \return ��ѯ�ɹ��������ַ�������λ�ã���ѯʧ�ܷ���npos
	size_t rfind( const char* s, size_t pos, size_t n ) const;
		
	/// �������ָ���ַ���
	/// \param s ��ѯ�ַ�����ַ
	/// \param pos ��ѯ��ʼλ�õ�ƫ����
	/// \return ��ѯ�ɹ��������ַ�������λ�ã���ѯʧ�ܷ���npos
	size_t rfind( const char* s, size_t pos = npos ) const;
		
	/// �����ѯָ���ַ�
	/// \param s ��ѯ�ַ�
	/// \param pos ��ѯ��ʼλ�õ�ƫ����
	/// \��ѯ�ɹ��������ַ�������λ�ã���ѯʧ�ܷ���npos
	size_t rfind( char c, size_t pos = npos ) const;
		
	/// ��ѯ��һ��ƥ��ָ���ַ�����λ��
	/// \param str ƥ���ַ���
	/// \param pos ��ʼƥ��ƫ����
	size_t find_first_of( CString const& str, size_t pos = 0 ) const;
		
	/// ��ѯ��һ��ƥ��ָ���ַ�����λ��
	/// \param s ƥ���ַ�����ַ
	/// \param pos ��ʼƥ��ƫ����
	/// \param n ָ��ƥ���ַ�������
	size_t find_first_of( const char* s, size_t pos, size_t n ) const;
		
	/// ��ѯ��һ��ƥ��ָ���ַ�����λ��
	/// \param s ƥ���ַ�����ַ
	/// \param pos ��ʼƥ��ƫ����
	size_t find_first_of( const char* s, size_t pos = 0 ) const;
		
	/// ��ѯ��һ��ƥ��ָ���ַ���λ��
	/// \param c ƥ���ַ�
	/// \param pos ��ʼƥ��ƫ����
	size_t find_first_of( char c, size_t pos = 0 ) const;
		
	/// �Ӻ���ǰ��ѯ�����ҵ�һ��ƥ�䵽ָ���ַ�����λ��
	/// \param str ƥ���ַ���
	/// \param pos ��ʼƥ��ƫ����
	size_t find_last_of( CString const& str, size_t pos = 0 ) const;
		
	/// �Ӻ���ǰ��ѯ�����ҵ�һ��ƥ�䵽ָ���ַ�����λ��
	/// \param s ƥ���ַ�����ַ
	/// \param pos ��ʼƥ��ƫ����
	/// \param n ָ��ƥ���ַ�������
	size_t find_last_of( const char* s, size_t pos, size_t n ) const;
		
	/// �Ӻ���ǰ��ѯ�����ҵ�һ��ƥ�䵽ָ���ַ�����λ��
	/// \param s ƥ���ַ�����ַ
	/// \param pos ��ʼƥ��ƫ����
	size_t find_last_of( const char* s, size_t pos = 0 ) const;
		
	/// �Ӻ���ǰ��ѯ����ѯ��һ��ƥ��ָ���ַ���λ��
	/// \param c ƥ���ַ�
	/// \param pos ��ʼƥ��ƫ����
	size_t find_last_of( char c, size_t pos = 0 ) const;
		
	/// ��ԭ�ַ����Ͻ�ȡ���ַ���
	/// \param pos ���ַ�����ʵλ��ƫ����
	/// \param n ���ַ�������
	CString substr( size_t pos = 0, size_t n = npos ) const;
		
	/// �Ƚ������ַ����Ƿ����
	/// \param str �Ƚ��ַ���
	int compare( CString const& str ) const;
		
	/// �Ƚ������ַ����Ƿ����
	/// \param pos1 ���Ƚ��ַ�������ʼƫ����
	/// \param n1 ָ�����Ƚ��ַ�������
	/// \param str �Ƚ��ַ���
	int compare( size_t pos1, size_t n1, CString const& str ) const;
		
	/// �Ƚ������ַ����Ƿ����
	/// \param pos1 ���Ƚ��ַ�������ʼƫ����
	/// \param n1 ָ�����Ƚ��ַ�������
	/// \param s �Ƚ��ַ�����ַ
	int compare( size_t pos1, size_t n1, const char* s ) const;
		
	/// �Ƚ������ַ����Ƿ����
	/// \param pos1 ���Ƚ��ַ�������ʼƫ����
	/// \param n1 ָ�����Ƚ��ַ�������
	/// \param s �Ƚ��ַ�����ַ
	/// \param n2 �Ƚϳ���
	int compare( size_t pos1, size_t n1, const char* s, size_t n2 ) const;
		
	/// �Ƚ������ַ����Ƿ����
	/// \param pos1 ���Ƚ��ַ�������ʼƫ����
	/// \param n1 ָ�����Ƚ��ַ�������
	/// \param str �Ƚ��ַ���
	/// \param pos2 �Ƚ��ַ�������ʼƫ����
	/// \param n2 ָ���Ƚ��ַ�������
	int compare( size_t pos1, size_t n1, CString const& str, 
		size_t pos2 ) const;
		
	/// �Ƚ������ַ����Ƿ����
	/// \param s �Ƚ��ַ�����ַ
	int compare( const char* s ) const;
		
	/// ���� + ������
	/// \param b ���ַ���
	CString operator + ( CString const& other ) const;
		
	/// ���� + ������
	/// \param b ���ַ���
	CString operator + ( const char* other ) const;

	/// ���� == ������
	/// \param b �Ƚ��ַ���
	bool operator == ( CString const& other ) const;
		
	/// ���� == ������
	/// \param b �Ƚ��ַ�����ַ
	bool operator == ( const char* other ) const;

	/// ���� != ������
	/// \param b �Ƚ��ַ�����ַ
	bool operator != ( CString const& other ) const;
		
	/// ���� != ������
	/// \param b �Ƚ��ַ�����ַ
	bool operator != ( const char* other ) const;

	/// ���� < ������
	/// \param b �Ƚ��ַ�����ַ
	bool operator < ( CString const& other ) const;
		
	/// ���� < ������
	/// \param b �Ƚ��ַ�����ַ
	bool operator < ( const char* other ) const;

	/// ���� <= ������
	/// \param b �Ƚ��ַ�����ַ
	bool operator <= ( CString const& other ) const;
		
	/// ���� <= ������
	/// \param b �Ƚ��ַ�����ַ
	bool operator <= ( const char* other ) const;

	/// ���� > ������
	/// \param b �Ƚ��ַ�����ַ
	bool operator > ( CString const& other ) const;
		
	/// ���� > ������
	/// \param b �Ƚ��ַ�����ַ
	bool operator > ( const char* other ) const;

	/// ���� >= ������
	/// \param b �Ƚ��ַ�����ַ
	bool operator >= ( CString const& other ) const;
		
	/// ���� >= ������
	/// \param b �Ƚ��ַ�����ַ
	bool operator >= ( const char* other ) const;

private:
	struct Internal;
	Internal* m_internal;
};

} /// namespace Infra
} /// namespace Dahua

#endif /// __DAHUA_INFRA_CSTRING_H__
