/*
 * This file is part of libdom.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 Bo Yang <struggleyb.nku@gmail.com>
 */

#ifndef dom_html_collection_h_
#define dom_html_collection_h_

#include <dom/core/exceptions.h>

struct dom_node;
struct dom_string;

typedef struct dom_html_collection dom_html_collection;

dom_exception dom_html_collection_get_length(dom_html_collection *col,
		unsigned long *len);
dom_exception dom_html_collection_item(dom_html_collection *col,
		unsigned long index, struct dom_node **node);
dom_exception dom_html_collection_named_item(dom_html_collection *col,
		struct dom_string *name, struct dom_node **node);

void dom_html_collection_ref(dom_html_collection *col);
void dom_html_collection_unref(dom_html_collection *col);

#endif

