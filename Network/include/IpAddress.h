#ifndef IPADDRESS_H
#define IPADDRESS_H
#include "SafeTypes.h"
#include <string>
#include <istream>
#include <ostream>

namespace wv {
	//класс предназначенный для работы с IPv4 адресами
	class IpAddress {
	public:

		//дефортный конструктор, создает пустой, "неправильный" адрес
		IpAddress();

		//принимает адрес в общеизвестной форме "127.0.0.1"
		IpAddress(const std::string& l_ip);
		IpAddress(const char* l_ip);

		//принимает четыре числа,
		//каждое из которых представляет отдельный байт ip адреса
		IpAddress(intU8 l_a, intU8 l_b, intU8 l_c, intU8 l_d);
		
		//использует напрямую системное представление ip адреса
		explicit IpAddress(intU32 l_ip);

		//конвертирует адрес в строку вида "127.0.0.1"
		std::string toString() const;

		//возвращает адрес в виде, удобном для обмена по сети
		intU32 toInteger() const;

		//возвращает адресть компьютера в локальной сети (192.168.1.56)
		static IpAddress GetLocalAddress();
		
		//на данный момент пустая
		static IpAddress GetPublicAddress();

		//представляет пустой/недействительный адрес
		static const IpAddress	None;
		
		//любой действительный адрес (0.0.0.0)
		static const IpAddress	Any;

		//"localhost" адресс
		static const IpAddress	LocalHost;

		//адрес для посыла информации сразу всем устройствам,
		//подключенным к локальной сети
		static const IpAddress	Broadcast;

	private:
		friend bool operator < (const IpAddress& l_left, const IpAddress& l_right);

		//преобразует строку, содержащую адресс в его системное представление
		void Resolve(const std::string& l_address);

		//адресс хранится как 32 битное беззнаковое число
		intU32	    m_address;

		//действительный/недействительный адресс
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
