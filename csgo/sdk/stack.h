#pragma once

class stack_t : public address_t
{
public:
	// ctor.
	__forceinline stack_t() : address_t{ *(uintptr_t *)((uintptr_t)_AddressOfReturnAddress() - sizeof(uintptr_t)) } { }

	// get return address.
	__forceinline address_t get_return_address() {
		if (!m_ptr)
			return address_t{};

		return *(uintptr_t*) (m_ptr + sizeof(uintptr_t));
	}

	// go up stack frame.
	__forceinline stack_t& next() {
		return *(stack_t*) m_ptr;
	}

	// get local variable.
	template< typename t = address_t >
	__forceinline t get_local(size_t offset) {
		return (t) (m_ptr - offset);
	}

	// get arg.
	template< typename t = address_t >
	__forceinline t get_arg(size_t offset) {
		return (t) (m_ptr + offset);
	}
};
