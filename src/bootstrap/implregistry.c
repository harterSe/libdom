/*
 * This file is part of libdom.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2007 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include <stddef.h>

#include <dom/bootstrap/implpriv.h>
#include <dom/bootstrap/implregistry.h>

#include <dom/core/impllist.h>

/**
 * Item in list of registered DOM implementation sources
 */
struct dom_impl_src_item {
	struct dom_implementation_source *source;	/**< Source */

	struct dom_impl_src_item *next;		/**< Next in list */
	struct dom_impl_src_item *prev;		/**< Previous in list */
};

static struct dom_impl_src_item *sources; /**< List of registered sources */

/**
 * Retrieve a DOM implementation from the registry
 *
 * \param features  String containing required features
 * \param impl      Pointer to location to receive implementation
 * \param alloc     Function to (de)allocate memory
 * \param pw        Pointer to client-specific private data
 * \return DOM_NO_ERR on success, DOM_NO_MEM_ERR on memory exhaustion
 *
 * Any memory allocated by this call should be allocated using
 * the provided memory (de)allocation function. The implementation's
 * destroy() method will be called once it is no longer used.
 *
 * The implementation will be referenced, so the client need not
 * do this explicitly. The client must unref the implementation
 * once it has finished with it.
 */
dom_exception dom_implregistry_get_dom_implementation(
		struct dom_string *features,
		struct dom_implementation **impl,
		dom_alloc alloc, void *pw)
{
	struct dom_impl_src_item *item;
	struct dom_implementation *found = NULL;
	dom_exception err;

	for (item = sources; item; item = item->next) {
		err = item->source->get_dom_implementation(features, &found,
				alloc, pw);
		if (err != DOM_NO_ERR)
			return err;

		if (found != NULL)
			break;
	}

	*impl = found;

	return DOM_NO_ERR;
}

/**
 * Get a list of DOM implementations that support the requested
 * features
 *
 * \param features  String containing required features
 * \param list      Pointer to location to receive list
 * \param alloc     Function to (de)allocate memory
 * \param pw        Pointer to client-specific private data
 * \return DOM_NO_ERR on success, DOM_NO_MEM_ERR on memory exhaustion
 *
 * Any memory allocated by this call should be allocated using
 * the provided memory (de)allocation function. The ::alloc/::pw
 * pair must be stored on the list object, such that the list
 * and its contents may be freed once they are no longer needed.
 *
 * List nodes reference the implementation objects they point to.
 *
 * The list will be referenced, so the client need not do this
 * explicitly. The client must unref the list once it has finished
 * with it.
 */
dom_exception dom_implregistry_get_dom_implementation_list(
		struct dom_string *features,
		struct dom_implementation_list **list,
		dom_alloc alloc, void *pw)
{
	struct dom_implementation_list *l;
	struct dom_impl_src_item *item;
	dom_exception err;

	l = alloc(NULL, sizeof(struct dom_implementation_list), pw);
	if (l == NULL)
		return DOM_NO_MEM_ERR;

	l->head = NULL;
	l->alloc = alloc;
	l->pw = pw;
	l->refcnt = 1;

	for (item = sources; item; item = item->next) {
		struct dom_implementation_list *plist = NULL;
		struct dom_implementation_list_item *plast = NULL;

		err = item->source->get_dom_implementation_list(features,
				&plist, alloc, pw);
		if (err != DOM_NO_ERR) {
			dom_implementation_list_unref(l);
			return err;
		}

		if (plist == NULL)
			continue;

		if (plist->head == NULL) {
			dom_implementation_list_unref(plist);
			continue;
		}

		/* Get last item in list for this source */
		for (plast = plist->head; plast; plast = plast->next) {
			if (plast->next == NULL)
				break;
		}

		/* Prepend list for this source onto result list */
		plast->next = l->head;
		if (l->head != NULL)
			l->head->prev = plast;
		l->head = plist->head;

		/* Invalidate entire content of list for this source */
		plist->head = NULL;

		/* And unref it */
		dom_implementation_list_unref(plist);
	}

	if (l->head == NULL) {
		*list = NULL;
		dom_implementation_list_unref(l);
	} else {
		*list = l;
	}

	return DOM_NO_ERR;
}

/**
 * Register a DOM implementation source with the DOM library
 *
 * \param source  The implementation source to register
 * \param alloc   Memory (de)allocation function
 * \param pw      Pointer to client-specific private data
 * \return DOM_NO_ERR on success, DOM_NO_MEM_ERR on memory exhaustion.
 */
dom_exception dom_register_source(struct dom_implementation_source *source,
		dom_alloc alloc, void *pw)
{
	struct dom_impl_src_item *item;

	item = alloc(NULL, sizeof(struct dom_impl_src_item), pw);
	if (item == NULL)
		return DOM_NO_MEM_ERR;

	item->source = source;

	item->next = sources;
	item->prev = NULL;

	if (sources != NULL)
		sources->prev = item;

	sources = item;

	return DOM_NO_ERR;
}
