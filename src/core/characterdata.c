/*
 * This file is part of libdom.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2007 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include <dom/core/characterdata.h>
#include <dom/core/string.h>

#include "core/node.h"
#include "utils/utils.h"

/**
 * DOM character data node
 */
struct dom_characterdata {
	struct dom_node base;		/**< Base node */
};

/**
 * Retrieve data from a character data node
 *
 * \param cdata  Character data node to retrieve data from
 * \param data   Pointer to location to receive data
 * \return DOM_NO_ERR.
 *
 * The returned string will have its reference count increased. It is
 * the responsibility of the caller to unref the string once it has
 * finished with it.
 *
 * DOM3Core states that this can raise DOMSTRING_SIZE_ERR. It will not in
 * this implementation; dom_strings are unbounded.
 */
dom_exception dom_characterdata_get_data(struct dom_characterdata *cdata,
		struct dom_string **data)
{
	UNUSED(cdata);
	UNUSED(data);

	return DOM_NOT_SUPPORTED_ERR;
}

/**
 * Set the content of a character data node
 *
 * \param cdata  Node to set the content of
 * \param data   New value for node
 * \return DOM_NO_ERR                      on success,
 *         DOM_NO_MODIFICATION_ALLOWED_ERR if ::cdata is readonly.
 *
 * The new content will have its reference count increased, so the caller
 * should unref it after the call (as the caller should have already claimed
 * a reference on the string). The node's existing content will be unrefed.
 */
dom_exception dom_characterdata_set_data(struct dom_characterdata *cdata,
		struct dom_string *data)
{
	UNUSED(cdata);
	UNUSED(data);

	return DOM_NOT_SUPPORTED_ERR;
}

/**
 * Get the length (in characters) of a character data node's content
 *
 * \param cdata   Node to read content length of
 * \param length  Pointer to location to receive character length of content
 * \return DOM_NO_ERR.
 */
dom_exception dom_characterdata_get_length(struct dom_characterdata *cdata,
		unsigned long *length)
{
	UNUSED(cdata);
	UNUSED(length);

	return DOM_NOT_SUPPORTED_ERR;
}

/**
 * Extract a range of data from a character data node
 *
 * \param cdata   The node to extract data from
 * \param offset  The character offset of substring to extract
 * \param count   The number of characters to extract
 * \param data    Pointer to location to receive substring
 * \return DOM_NO_ERR         on success,
 *         DOM_INDEX_SIZE_ERR if ::offset is greater than the number of
 *                            characters in ::cdata.
 *
 * The returned string will have its reference count increased. It is
 * the responsibility of the caller to unref the string once it has
 * finished with it.
 *
 * DOM3Core states that this can raise DOMSTRING_SIZE_ERR. It will not in
 * this implementation; dom_strings are unbounded.
 */
dom_exception dom_characterdata_substring_data(
		struct dom_characterdata *cdata, unsigned long offset,
		unsigned long count, struct dom_string **data)
{
	UNUSED(cdata);
	UNUSED(offset);
	UNUSED(count);
	UNUSED(data);

	return DOM_NOT_SUPPORTED_ERR;
}

/**
 * Append data to the end of a character data node's content
 *
 * \param cdata  The node to append data to
 * \param data   The data to append
 * \return DOM_NO_ERR                      on success,
 *         DOM_NO_MODIFICATION_ALLOWED_ERR if ::cdata is readonly.
 */
dom_exception dom_characterdata_append_data(struct dom_characterdata *cdata,
		struct dom_string *data)
{
	UNUSED(cdata);
	UNUSED(data);

	return DOM_NOT_SUPPORTED_ERR;
}

/**
 * Insert data into a character data node's content
 *
 * \param cdata   The node to insert into
 * \param offset  The character offset to insert at
 * \param data    The data to insert
 * \return DOM_NO_ERR                      on success,
 *         DOM_INDEX_SIZE_ERR              if ::offset is greater than the
 *                                         number of characters in ::cdata,
 *         DOM_NO_MODIFICATION_ALLOWED_ERR if ::cdata is readonly.
 */
dom_exception dom_characterdata_insert_data(struct dom_characterdata *cdata,
		unsigned long offset, struct dom_string *data)
{
	UNUSED(cdata);
	UNUSED(offset);
	UNUSED(data);

	return DOM_NOT_SUPPORTED_ERR;
}

/**
 * Delete data from a character data node's content
 *
 * \param cdata   The node to delete from
 * \param offset  The character offset to start deletion from
 * \param count   The number of characters to delete
 * \return DOM_NO_ERR                      on success,
 *         DOM_INDEX_SIZE_ERR              if ::offset is greater than the
 *                                         number of characters in ::cdata,
 *         DOM_NO_MODIFICATION_ALLOWED_ERR if ::cdata is readonly.
 */
dom_exception dom_characterdata_delete_data(struct dom_characterdata *cdata,
		unsigned long offset, unsigned long count)
{
	UNUSED(cdata);
	UNUSED(offset);
	UNUSED(count);

	return DOM_NOT_SUPPORTED_ERR;
}

/**
 * Replace a section of a character data node's content
 *
 * \param cdata   The node to modify
 * \param offset  The character offset of the sequence to replace
 * \param count   The number of characters to replace
 * \param data    The replacement data
 * \return DOM_NO_ERR                      on success,
 *         DOM_INDEX_SIZE_ERR              if ::offset is greater than the
 *                                         number of characters in ::cdata,
 *         DOM_NO_MODIFICATION_ALLOWED_ERR if ::cdata is readonly.
 */
dom_exception dom_characterdata_replace_data(struct dom_characterdata *cdata,
		unsigned long offset, unsigned long count,
		struct dom_string *data)
{
	UNUSED(cdata);
	UNUSED(offset);
	UNUSED(count);
	UNUSED(data);

	return DOM_NOT_SUPPORTED_ERR;
}
