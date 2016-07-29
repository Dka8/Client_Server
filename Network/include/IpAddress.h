#ifndef IPADDRESS_H
#define IPADDRESS_H
#include "SafeTypes.h"
#include <string>
#include <istream>
#include <ostream>

namespace wv {
	//����� ��������������� ��� ������ � IPv4 ��������
	class IpAddress {
	public:

		//��������� �����������, ������� ������, "������������" �����
		IpAddress();

		//��������� ����� � ������������� ����� "127.0.0.1"
		IpAddress(const std::string& l_ip);
		IpAddress(const char* l_ip);

		//��������� ������ �����,
		//������ �� ������� ������������ ��������� ���� ip ������
		IpAddress(intU8 l_a, intU8 l_b, intU8 l_c, intU8 l_d);
		
		//���������� �������� ��������� ������������� ip ������
		explicit IpAddress(intU32 l_ip);

		//������������ ����� � ������ ���� "127.0.0.1"
		std::string toString() const;

		//���������� ����� � ����, ������� ��� ������ �� ����
		intU32 toInteger() const;

		//���������� ������� ���������� � ��������� ���� (192.168.1.56)
		static IpAddress GetLocalAddress();
		
		//�� ������ ������ ������
		static IpAddress GetPublicAddress();

		//������������ ������/���������������� �����
		static const IpAddress	None;
		
		//����� �������������� ����� (0.0.0.0)
		static const IpAddress	Any;

		//"localhost" ������
		static const IpAddress	LocalHost;

		//����� ��� ������ ���������� ����� ���� �����������,
		//������������ � ��������� ����
		static const IpAddress	Broadcast;

	private:
		friend bool operator < (const IpAddress& l_left, const IpAddress& l_right);

		//����������� ������, ���������� ������ � ��� ��������� �������������
		void Resolve(const std::string& l_address);

		//������ �������� ��� 32 ������ ����������� �����
		intU32	    m_address;

		//��������������/���������������� ������
		bool		m_valid;
	};
	bool operator == (const IpAddress& l_left, const IpAddress& l_right);
	bool operator != (const IpAddress& l_left, const IpAddress& l_right);
	bool operator < (const IpAddress& l_left, const IpAddress& l_right);
	bool operator > (const IpAddress& l_left, const IpAddress& l_right);
	bool operator <= (const IpAddress& l_left, const IpAddress& l_right);
	bool operator >= (const IpAddress& l_left, const IpAddress& l_right);

	std::istream& operator >> (std::istream& cin, IpAddress& l_address);
	std::ostream& operator << (std::ostream& cout, const IpAddress& l_address);
}

#endif // IPADDRESS_H
