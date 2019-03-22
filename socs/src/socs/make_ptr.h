#pragma once

#include <memory>

namespace socs {

using std::unique_ptr;

#ifdef MAKE_PTR

template<typename _Tp>
struct _MakeUniq {
	typedef unique_ptr<_Tp> __single_object;
};

/// std::make_unique for single objects
template<typename _Tp, typename ... _Args>
inline typename _MakeUniq<_Tp>::__single_object make_unique(_Args&&... __args) {
	return unique_ptr<_Tp>(new _Tp(std::forward<_Args>(__args)...));
}

#endif

} // namespace socs

