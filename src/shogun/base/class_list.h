/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Sergey Lisitsyn, Soeren Sonnenburg, Giovanni De Toni, Yuyu Zhang
 */

#ifndef __SG_CLASS_LIST_H__
#define __SG_CLASS_LIST_H__

#include <shogun/base/SGObject.h>
#include <shogun/lib/config.h>

#include <shogun/lib/DataType.h>
#include <shogun/lib/exception/ShogunException.h>

#include <shogun/io/SGIO.h>

#include <set>
#include <string>
#include <queue>

namespace shogun {
	class SGObject;

	/** new shogun instance
	 * @param sgserializable_name
	 * @param generic
	 */
	std::shared_ptr<SGObject> create(const char* sgserializable_name, EPrimitiveType generic);

	/** Use Levenshtein distance to find the most similar name
	 *
	 */
	std::string find_correct_name(const std::string& name);

	/** Creates new shogun instance, typed.
	 *
	 * Throws an exception in case there is no such classname or
	 * the requested type and the object's type do not match.
	 *
	 */
	template <class T>
	std::shared_ptr<T> create_object(
	    const char* name,
	    EPrimitiveType pt = PT_NOT_GENERIC) noexcept(false)
	{
		auto object = create(name, pt);
		if (!object)
		{
			const auto& correct_name = find_correct_name(name);
			error(
			    "{} {} does not exist. Did you mean {} ?", name_lookup<T>(), name, correct_name);
		}
		auto cast = std::dynamic_pointer_cast<T>(object);
		if (cast == nullptr)
		{
			error("could not cst");
		}
		return cast;
	}

	/** Returns all available object names
	 *
	 */
	std::set<std::string> available_objects();
}

#endif /* __SG_CLASS_LIST_H__  */
