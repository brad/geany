/*
 *      filetypes.h - this file is part of Geany, a fast and lightweight IDE
 *
 *      Copyright 2005-2009 Enrico Tröger <enrico(dot)troeger(at)uvena(dot)de>
 *      Copyright 2006-2009 Nick Treleaven <nick(dot)treleaven(at)btinternet(dot)com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $Id$
 */


#ifndef GEANY_FILETYPES_H
#define GEANY_FILETYPES_H 1

#include "Scintilla.h"
#include "ScintillaWidget.h"

#ifdef GEANY_PRIVATE
#include "build.h"
#endif


typedef enum
{
	GEANY_FILETYPES_NONE = 0,	/* first filetype is always None & must be 0 */

	GEANY_FILETYPES_PHP,
	GEANY_FILETYPES_BASIC,	/* FreeBasic */
	GEANY_FILETYPES_MATLAB,
	GEANY_FILETYPES_RUBY,
	GEANY_FILETYPES_LUA,
	GEANY_FILETYPES_FERITE,
	GEANY_FILETYPES_YAML,
	GEANY_FILETYPES_C,
	GEANY_FILETYPES_NSIS,
	GEANY_FILETYPES_GLSL,
	GEANY_FILETYPES_PO,
	GEANY_FILETYPES_MAKE,
	GEANY_FILETYPES_TCL,
	GEANY_FILETYPES_XML,
	GEANY_FILETYPES_CSS,
	GEANY_FILETYPES_REST,
	GEANY_FILETYPES_HASKELL,
	GEANY_FILETYPES_JAVA,
	GEANY_FILETYPES_CAML,
	GEANY_FILETYPES_AS,
	GEANY_FILETYPES_R,
	GEANY_FILETYPES_DIFF,
	GEANY_FILETYPES_HTML,
	GEANY_FILETYPES_PYTHON,
	GEANY_FILETYPES_CS,
	GEANY_FILETYPES_PERL,
	GEANY_FILETYPES_VALA,
	GEANY_FILETYPES_PASCAL,
	GEANY_FILETYPES_LATEX,
	GEANY_FILETYPES_ASM,
	GEANY_FILETYPES_CONF,
	GEANY_FILETYPES_HAXE,
	GEANY_FILETYPES_CPP,
	GEANY_FILETYPES_SH,
	GEANY_FILETYPES_FORTRAN,
	GEANY_FILETYPES_SQL,
	GEANY_FILETYPES_F77,
	GEANY_FILETYPES_DOCBOOK,
	GEANY_FILETYPES_D,
	GEANY_FILETYPES_JS,
	GEANY_FILETYPES_VHDL,
	GEANY_FILETYPES_ADA,
	GEANY_FILETYPES_CMAKE,
	GEANY_FILETYPES_MARKDOWN,
	GEANY_FILETYPES_TXT2TAGS,
	GEANY_FILETYPES_ABC,
	GEANY_FILETYPES_VERILOG,
	/* ^ append items here */
	GEANY_MAX_BUILT_IN_FILETYPES	/* Don't use this, use filetypes_array->len instead */
}
filetype_id;

typedef enum
{
	GEANY_FILETYPE_GROUP_NONE,
	GEANY_FILETYPE_GROUP_COMPILED,
	GEANY_FILETYPE_GROUP_SCRIPT,
	GEANY_FILETYPE_GROUP_MARKUP,
	GEANY_FILETYPE_GROUP_MISC,
	GEANY_FILETYPE_GROUP_COUNT
}
GeanyFiletypeGroupID;


/* Safe wrapper to get the id field of a possibly NULL filetype pointer.
 * This shouldn't be necessary since GeanyDocument::file_type is always non-NULL. */
#define FILETYPE_ID(filetype_ptr) \
	(((filetype_ptr) != NULL) ? (filetype_ptr)->id : GEANY_FILETYPES_NONE)

/** Represents a filetype. */
struct GeanyFiletype
{
	filetype_id		  id;				/**< Index in @c filetypes_array. */
	/** Represents the langType of tagmanager (see the table
	 * in tagmanager/parsers.h), -1 represents all, -2 none. */
	langType 		  lang;
	gchar			 *name;				/**< Short name, e.g. "C". */
	gchar			 *title;			/**< Shown in the file open dialog. E.g. "C source file". */
	gchar			 *extension;		/**< Default file extension for new files, or @c NULL. */
	gchar			**pattern;			/**< Array of filename-matching wildcard strings. */
	gchar			 *context_action_cmd;
	gchar			 *comment_open;
	gchar			 *comment_close;
	gboolean		  comment_use_indent;
	GeanyFiletypeGroupID group;
	gchar			 *error_regex_string;
	GeanyFiletype	 *lexer_filetype;

	struct GeanyFiletypePrivate	*priv;	/* must be last, append fields before this item */
#ifdef GEANY_PRIVATE
	/* Do not use following fields in plugins */
	GeanyBuildCommand *filecmds;	/* these need to be visible since used in build.c so not in private part */
	GeanyBuildCommand *ftdefcmds;	/* filetype dependent defaults for non_ft commands */
	GeanyBuildCommand *execcmds;
	GeanyBuildCommand *homefilecmds;
	GeanyBuildCommand *homeexeccmds;
	GeanyBuildCommand *projfilecmds;
	GeanyBuildCommand *projexeccmds;
	gint			 project_list_entry;
	gchar			 *projerror_regex_string;
	gchar			 *homeerror_regex_string;
	gboolean		  home_save_needed;
#endif
};

extern GPtrArray *filetypes_array;

/** Wrap filetypes_array so it can be used with C array syntax.
 * Example: filetypes[GEANY_FILETYPES_C]->name = ...;
 * @see filetypes_index(). */
#define filetypes	((GeanyFiletype **)GEANY(filetypes_array)->pdata)

extern GSList *filetypes_by_title;


GeanyFiletype *filetypes_lookup_by_name(const gchar *name);

GeanyFiletype *filetypes_find(GCompareFunc predicate, gpointer user_data);


void filetypes_init(void);

void filetypes_init_types(void);

void filetypes_read_extensions(void);

void filetypes_reload(void);


GeanyFiletype *filetypes_index(gint idx);

GeanyFiletype *filetypes_detect_from_document(GeanyDocument *doc);

GeanyFiletype *filetypes_detect_from_extension(const gchar *utf8_filename);

GeanyFiletype *filetypes_detect_from_file(const gchar *utf8_filename);

void filetypes_free_types(void);

void filetypes_load_config(gint ft_id, gboolean reload);

void filetypes_save_commands(void);

void filetypes_select_radio_item(const GeanyFiletype *ft);

GtkFileFilter *filetypes_create_file_filter(const GeanyFiletype *ft);

GtkFileFilter *filetypes_create_file_filter_all_source(void);

gchar *filetypes_get_conf_extension(gint filetype_idx);

gboolean filetype_has_tags(GeanyFiletype *ft);

gboolean filetypes_parse_error_message(GeanyFiletype *ft, const gchar *message,
		gchar **filename, gint *line);

#endif
