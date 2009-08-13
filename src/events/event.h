/*
 * This file is part of libdom.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2009 Bo Yang <struggleyb.nku@gmail.com>
 */

#ifndef dom_internal_events_event_h_
#define dom_internal_events_event_h_

#include <inttypes.h>

#include <dom/events/event_target.h>
#include <dom/events/event.h>

#include "utils/list.h"

struct lwc_string_s;
struct dom_document;

/* The private virtual table */
struct dom_event_private_vtable {
	void (*destroy)(dom_event *evt);
};

/**
 * The Event Ojbect
 */
struct dom_event {
	struct lwc_string_s *type;	/**< The type of the event */
	dom_event_target *target;	/**< The event target */
	dom_event_target *current; 	/**< The current event target */
	dom_event_flow_phase phase;		/**< The event phase */
	bool bubble;	/**< Whether this event is a bubbling event */
	bool cancelable;	/**< Whether this event is cancelable */
	unsigned int timestamp;
			/**< The timestamp this event is created */

	struct lwc_string_s *namespace;
			/**< The namespace of this event */

	struct dom_document *doc;
			/**< The document which create this event */

	bool stop; 		/**< Whether stopPropagation is called */
	bool stop_now;	/**< Whether stopImmediatePropagation is called */
	bool prevent_default;
			/**< Whether the default action is prevented */

	bool custom;	/**< Whether this is a custom event */

	uint32_t refcnt;	/**< The reference count of this object */

	struct dom_event_private_vtable *vtable;
			/**< The private virtual function table of Event */
	bool in_dispatch;	/**< Whether this event is in dispatch */
};

/* Constructor */
dom_exception _dom_event_create(struct dom_document *doc, 
		struct dom_event **evt);

/* Destructor */
void _dom_event_destroy(struct dom_document *doc, struct dom_event *evt);

/* Initialise function */
dom_exception _dom_event_initialise(struct dom_document *doc, 
		struct dom_event *evt);

/* Finalise function */
void _dom_event_finalise(struct dom_document *doc, struct dom_event *evt);


static inline void dom_event_destroy(struct dom_event *evt)
{
	evt->vtable->destroy(evt);
}
#define dom_event_destroy(e) dom_event_destroy((struct dom_event *) (e))

#endif
