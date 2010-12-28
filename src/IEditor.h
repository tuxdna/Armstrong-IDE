/*
 * armstrong-ide
 * Copyright (C) 2010 Saleem Ansari <tuxdna@gmail.com>
 *
 * Armstrong-IDE is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Armstrong-IDE is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __I_EDITOR__
#define __I_EDITOR__

/**
 * @short_description: Text editor assist interface
 */

#include <gtkmm.h>
#include <glibmm.h>
#include <list>

#include "Iterable.h"
#include "IProvider.h"

namespace armstrong {

/**
 * @title: IEditor
 * @short_description: Text editor interface
 *
 */

class IEditor {
public:

	// default virtual destructor
	virtual ~IEditor() {
	}

	enum Error {
		DOESNT_EXIST
	};

	/**
	 * TEXT: Normal text
	 * KEYWORD: A keyword of the programming language
	 * COMMENT: A comment
	 * STRING: A string
	 *
	 * This enumeration is used to specify the type of text. Note that not all
	 * editors implement this.
	 */
	enum Attribute {
		TEXT, KEYWORD, COMMENT, STRING
	};


	/**
	 * @position: The iter position where @ch is added.
	 * @ch: The character that has been added.
	 * @obj: Self
	 *
	 * This signal is emitted when any character is added inside the editor.
	 * The newly added character is @ch which has been inserted at @position.
	 */
	// virtual void char_added(GObject *position, gchar ch) = 0; //signal
	sigc::signal<void, GObject *, gchar> char_added;

	/**
	 * The signal is emitted when the user presses backspace
	 */
	//virtual void backspace() = 0; //signal
	sigc::signal<void> backspace;

	/**
	 * @position: The iter position where change happend.
	 * @added: TRUE if added, FALSE if deleted.
	 * @length: Length of the text changed.
	 * @lines: Number of lines added or removed.
	 * @text: The text added or removed.
	 *
	 * This signal is emitted when any text change happens in editor.
	 * The changes begin at @position. @text is not garanteed to be NULL
	 * terminated. Use @length to read the text. @lines represent the
	 * number of line breaks in the added or removed text.
	 */
	//	virtual void changed(GObject *position, gboolean added, gint length,
	//			gint lines, const gchar *text) = 0; //signal

	sigc::signal<void, GObject *, gboolean, gint, gint, const gchar *> changed;

	/**
	 * @double_click: whether the line marks gutter was double clicked
	 * @location: location of the clicked marker
	 *
	 * The signal is emitted when the user clicks on a marker
	 */
	// virtual void line_marks_gutter_clicked(gint location) = 0; //signal
	sigc::signal<void, gint> line_marks_gutter_clicked;

	virtual Gtk::Widget * getUi() = 0;
	virtual std::string getFilename() = 0;
	virtual void setFilename(std::string) = 0;

	/**
	 * Returns the tabsize (in spaces) currently used by the editor.
	 *
	 * Returns: tabsize in number of spaces
	 */
	virtual gint get_tabsize() = 0;

	/**
	 * @tabsize: Tabsize in spaces
	 *
	 * Sets the tabsize of the editor.
	 */
	virtual void set_tabsize(gint tabsize) = 0;

	/**
	 * Returns if the editor uses spaces for filling up tab characters.
	 *
	 * Returns: TRUE if yes, FALSE if no.
	 */
	virtual gboolean get_use_spaces() = 0;

	/**
	 * @use_spaces: TRUE to use spaces, FALSE to use tab char directly.
	 *
	 * Sets if the editor should use spaces for filling up tab characters.
	 */
	virtual void set_use_spaces(gboolean use_spaces) = 0;

	/**
	 * @auto_indent: TRUE to enable auto-indent, FALSE to disable
	 *
	 * Sets whether the editor should auto-indent itself. A plugin that does
	 * custom auto-indent can set this to false and override the preferences
	 * setting
	 */
	virtual void set_auto_indent(gboolean auto_indent) = 0;

	/**
	 * @position_start: Start position of chars to erase.
	 * @position_end: End position of chars to erase.
	 *
	 * Erases the chars between positions pointed by @position_start and
	 * @position_end. The character pointed by @position_start is included,
	 * while pointed by @position_end is not include in the range. After
	 * the erase operation, all active iters, except these two, are no
	 * longer guranteed to be valid. At the end the operation, these two
	 * iters point to the same position which is the position where erase
	 * happend (usually the original @position_start position).
	 */
	virtual void erase(Iterable *position_start, Iterable *position_end) = 0;

	/**
	 * Empties the whole editor buffer. There will be zero characters.
	 * After the erase operation, none of the active iters are guranteed
	 * to be valid.
	 */
	virtual void erase_all() = 0;

	/**
	 * @position: Character position in editor where insert will take place.
	 * @text: Text to append.
	 * @length: Length of @text to use.
	 *
	 * Inserts @length characters from @text buffer at given @position of
	 * editor buffer. If @length is -1, the whole @text is used.
	 */
	virtual void insert(Iterable *position, const gchar *text, gint length) = 0;

	/**
	 * @text: Text to append.
	 * @length: Length of @text to use.
	 *
	 * Appends @length characters from @text buffer at the end of editor
	 * buffer. If @length is -1, the whole @text is used. @length is in bytes.
	 */
	virtual void append(const gchar *text, gint length) = 0;

	/**
	 * @lineno: line number where carat will be moved.
	 *
	 * Carat is moved to the given @lineno line and text view is scrolled to
	 * bring it in viewable area of the editor.
	 */
	virtual void goto_line(gint lineno) = 0;

	/**
	 * Carat is moved to the begining of editor and text view is scrolled to
	 * bring it in viewable area of the editor.
	 */
	virtual void goto_start() = 0;

	/**
	 * Carat is moved to the end of editor and text view is scrolled to
	 * bring it in viewable area of the editor.
	 */
	virtual void goto_end() = 0;

	/**
	 * @position: Character position where carat will be moved.
	 *
	 * Carat is moved to the given @position and text view is scrolled to
	 * bring @position in viewable area of the editor.
	 */
	virtual void goto_position(Iterable *position) = 0;

	/**
	 * @begin: Begining iterator
	 * @end: End iterator
	 *
	 * Gets text characters beginning from @begin (including char
	 * pointed by @begin) and ending with @end (excluding character
	 * pointed by @end). The characters returned are utf-8 encoded.
	 * The iterators @begin and @end could be in either order. The returned
	 * text, however, is in right order. If both @begin and @end points
	 * to the same position, NULL is returned.
	 *
	 * Returns: A buffer of utf-8 characters.
	 * The returned buffer must be freed when no longer required.
	 */
	virtual gchar* get_text(Iterable *begin, Iterable *end) = 0;

	/**
	 * Gets all text characters in the editor.
	 * The characters returned are utf-8 encoded.
	 *
	 * Returns: A buffer of utf-8 characters containing all text from editor.
	 * The returned buffer must be freed when no longer required.
	 */
	virtual gchar* get_text_all() = 0;

	/**
	 * @position: Position you want to know the line from
	 *
	 * Get the line number in which @position locates.
	 * Returns: Line which corresponds to @position
	 *
	 */
	virtual int get_line_from_position(Iterable *position) = 0;

	/**
	 * Obtains current line number on which carat is.
	 *
	 * Return value: Line number.
	 */
	virtual gint get_lineno() = 0;

	/**
	 * Get length of complete text in editor. This will be the total
	 * number of bytes in the file or buffer.
	 *
	 * Return value: Text length.
	 */
	virtual gint get_length() = 0;

	/**
	 * Obtains the word on which carat is currently on.
	 *
	 * Return value: Current word.
	 */
	virtual gchar* get_current_word() = 0;

	/**
	 * Obtains number of the current column in the editor.
	 *
	 * Return value: Current column.
	 */
	virtual gint get_column() = 0;

	/**
	 * @line: fixme
	 * Returns: fixme
	 */
	virtual Iterable* get_line_begin_position(gint line) = 0;

	/**
	 * @line: fixme
	 * Returns: fixme
	 */
	virtual Iterable *get_line_end_position(gint line) = 0;

	/**
	 * Obtains editor overwirte mode: TRUE = Override, FALSE = Insert.
	 *
	 * Return value: editor mode.
	 */
	virtual gboolean get_overwrite() = 0;

	/**
	 * @menu: Popupmenu
	 *
	 * Set Editor popup menu. This is the menu shown in the editor when one
	 * right-clicks on it.
	 *
	 */
	virtual void set_popup_menu(GtkWidget *menu) = 0;

	/*
	 * Get current caret position in integer character offset.
	 *
	 * Returns: Current character position since the beginning of file.
	 */
	virtual gint get_offset() = 0;

	/*
	 * Get current caret position.
	 *
	 * Returns: Iterator that points to the current position.
	 */
	virtual Iterable* get_position() = 0;

	/**
	 * @offset: Character offset position where the iterator will be set
	 *
	 * Creates and returns an Iterable object for editor cells. It is
	 * placed at the unicode character position where the given offset
	 * @offset happens to fall. The returned Iterable* is cell (character)
	 * iter and not byte iter, so all iter operations
	 * on it are character (not byte) iteration, including all position
	 * and index references in the iter.
	 *
	 * The iter must be unreferrenced by the caller when done.
	 * The iter navigates (next/previous) in step of unicode
	 * characters (one unicode character == one cell).
	 *
	 * Retrun value: a newly created iter of IEditorCell placed at the
	 * given @offset position.
	 */
	virtual Iterable* get_position_from_offset(gint offset) = 0;

	/**
	 * Gets the iter positioned at the start of the editor buffer.
	 *
	 * Return value: Cell iter set to the begining of the editor.
	 */
	virtual Iterable* get_start_position() = 0;

	/**
	 * Gets the iter positioned at the end of the editor buffer. The
	 * returned iter is the end-iter which does not point to any valid
	 * character in the buffer (it is pointed one step beyond the last
	 * valid character).
	 *
	 * Retrun value: Cell iter set to the end of the editor (end-iter).
	 */
	virtual Iterable* get_end_position() = 0;

};

class IEditorAssist {
public:
	// default virtual destructor
	virtual ~IEditorAssist() {
	}

	struct Proposal {
		gchar* label;
		gchar* markup;
		gchar* info;
		gchar* text;
		GdkPixbuf* icon;
		gpointer data;
	};

	/*
	 * @provider: a IProvider
	 *
	 * Add a provider to the list of completion providers
	 */
	virtual void add(IProvider* provider) = 0;

	/*
	 * @provider: a IProvider
	 *
	 * Remove a provider from the list of completion providers
	 */
	virtual void remove(IProvider* provider) = 0;

	/*
	 * @provider: a IProvider (can be NULL to use all providers)
	 *
	 * Force invokation of a provider at the current cursor position.
	 * That means that provider_populate() will be called on the
	 * provider.
	 */
	virtual void invoke(IProvider* provider) = 0;

	/*
	 * @provider: a IProvider
	 * @proposals: a list of IProposals
	 * @finished: whether is was the last call in an async operation
	 *
	 * Add the list of proposals for the current population. You can add
	 * proposals async as long as the last call sets finished to TRUE. That
	 * is usually called by the IProvider after it was triggered by
	 * provider_populate()
	 *
	 */
	virtual void proposals(IProvider* provider, GList* proposals,
			gboolean finished) = 0;
};


/**
 * @title: IEditorCell
 * @short_description: Text editor character cell
 *
 * Represents a cell in editor. A cell corresponds to a unicode
 * character along with all associated styles (such as colors and font).
 * A cell may or may not have style. If style is supported in the
 * editor, it is assumed all cells will have styles and hence every
 * IEditorCell interface instance will have additionally
 * IEditorCellStyle implemented.
 */

class IEditorCell {
public:
	// default virtual destructor
	virtual ~IEditorCell() {
	}

	/**
	 * Returns the unicode character in this cell. A NULL terminated
	 * string is returned that is the multibyte unicode character.
	 * NULL is returned if the cell does not have any character.
	 *
	 * Returns: a newly created string representing the cell's unicode
	 * character.
	 */
	virtual gchar *get_character() = 0;

	/**
	 * Gets the length of the cell in bytes. That is, length of the
	 * unicode character.
	 *
	 * Returns: Length of the unicode character.
	 */
	virtual gint get_length() = 0;

	/**
	 * Returns the byte of the unicode character in this cell at given
	 * index @char_index. @char_index can vary from 0 to length of the
	 * unicode string minus 1. Out of range index is not allowed
	 * (asserted) and return is undefined.
	 *
	 * Since there is dynamic allocation of unicode character string
	 * involved in editor_cell_get_character(), this function
	 * is mainly useful for fast iteration (such as copying data).
	 *
	 * Returns: a byte character.
	 */
	virtual gchar get_char(gint char_index) = 0;

	virtual IEditor::Attribute get_attribute() = 0;

};
/**
 * @title: IEditorCellStyle
 * @short_description: Text editor cell style interface
 * @see_also:
 * @stability: Unstable
 *
 */

class IEditorCellStyle {
public:
	// default virtual destructor
	virtual ~IEditorCellStyle() {
	}

	virtual gchar* get_font_description() = 0;
	virtual gchar* get_color() = 0;
	virtual gchar* get_background_color() = 0;
};
/**
 * @title: IEditorComment
 * @short_description: Text editor comment interface
 * @see_also:
 * @stability: Unstable
 *
 */

class IEditorComment {
public:
	// default virtual destructor
	virtual ~IEditorComment() {
	}

	/**
	 * Comment/Uncomment out selected block
	 */
	virtual void block() = 0;

	/**
	 * Comment/Uncomment out selected block
	 */
	virtual void box() = 0;

	/**
	 * Comment/Uncomment out selected block
	 */
	virtual void stream() = 0;
};
/**
 * @title: IEditorConvert
 * @short_description: Text editor convert interface
 */

class IEditorConvert {
public:
	// default virtual destructor
	virtual ~IEditorConvert() {
	}

	/**
	 * @start_position: Start position.
	 * @end_position: End position.
	 *
	 * change characters from start position to end position to uppercase.
	 *
	 */
	virtual void to_upper(Iterable *start_position, Iterable *end_position) = 0;

	/**
	 * @start_position: Start position.
	 * @end_position: End position.
	 *
	 * change characters from start position to end position to lowercase
	 *
	 */
	virtual void to_lower(Iterable *start_position, Iterable *end_position) = 0;
};
/**
 * @title: IEditorFactory
 * @short_description: Text editor factory that creates IEditor objects
 */

class IEditorFactory {
public:
	// default virtual destructor
	virtual ~IEditorFactory() {
	}

	/**
	 * @file: file to open
	 * @filename: filename to open
	 *
	 * Get a new GtkWidget* which implements IEditor
	 *
	 * Return value: An object implementing IEditor
	 */
	virtual IEditor* new_editor(GFile* file, const gchar* filename) = 0;
};
/**
 * @title: IEditorFolds
 * @short_description: Text editor folds inteface
 */
class IEditorFolds {
public:
	// default virtual destructor
	virtual ~IEditorFolds() {
	}

	/**
	 * Open all folds
	 */
	virtual void open_all() = 0;

	/**
	 * Close all folds
	 */
	virtual void close_all() = 0;

	/**
	 * Open/Close current fold
	 */
	virtual void toggle_current() = 0;
};
/**
 * @title: IEditorGoto
 * @short_description: Text editor navigation interface
 */
class IEditorGoto {
public:
	// default virtual destructor
	virtual ~IEditorGoto() {
	}

	/**
	 * Moves cursor to the start of the current block
	 */
	virtual void start_block() = 0;

	/**
	 * Moves cursor to the end of the current block
	 */
	virtual void end_block() = 0;

	/**
	 * Moves cursor to matching brace
	 */
	virtual void matching_brace() = 0;

};
/**
 * @title: IEditorHover
 * @short_description: Text editor hover interface
 */

class IEditorHover {
public:
	// default virtual destructor
	virtual ~IEditorHover() {
	}

	/* IEditorHover::hover-over:
	 * @obj: self
	 * @position: IEditorCell specifying the position the mouse is over
	 *
	 * The mouse is held for a moment over @position. This can be used to show
	 * all tooltip.
	 */
	virtual void hover_over(GObject* position) = 0; //signal

	/* IEditorHover::hover-leave
	 * @obj: self
	 * @position: IEditorCell specifying the position the mouse was over
	 *
	 * User moved the mouse away - can be used to clean up things done in
	 * #IEditorHover::hover-over
	 */
	virtual void hover_leave(GObject* position) = 0; //signal

	/**
	 * editor_hover_display:
	 * @obj: Self
	 * @info: String to display
	 * @err: Error propagation and reporting
	 *
	 * Show @info as tooltip
	 *
	 */
	virtual void display(Iterable* position, const gchar *info) = 0;
};
/**
 * @title: IEditorLanguage
 * @short_description: Text editor language interface
 */

class IEditorLanguage {
public:
	// default virtual destructor
	virtual ~IEditorLanguage() {
	}

	/* IEditorLanguage::language-changed:
	 * @language: new language
	 *
	 * the language of the editor changed to @language
	 */
	virtual void language_changed(const gchar *language) = 0; //signal

	/**
	 * Return a list of languages supported by the editor
	 * Note: These list contains the names in the form
	 * the editor implementation knows them
	 *
	 */
	virtual const std::list<const gchar*> get_supported_languages() = 0;

	/**
	 * Get a list of languages the editor can highlight
	 */

	virtual const gchar *get_language_name(const gchar* language) = 0;

	/**
	 * Return the name of the currently used language
	 */

	virtual const gchar *get_language() = 0;

	/**
	 * @language: Language
	 * Force the editor to use a given language
	 */

	virtual void set_language(const gchar* language) = 0;
};
/**
 * @title: IEditorLineMode
 * @short_description: Text editor line mode
 * @see_also:
 * @stability: Unstable
 *
 */
class IEditorLineMode {
public:
	// default virtual destructor
	virtual ~IEditorLineMode() {
	}

	/**
	 * IEditorLineModeType:
	 * LINE_MODE_LF: Line-Feed (Unix)
	 * LINE_MODE_CR: Carat return (Max)
	 * LINE_MODE_CRLF: Caret return + line-feed (Windows)
	 *
	 * This enumeration is used to specify the type of text. Note that not all
	 * editors implement this.
	 */
	enum Type {
		LF, CR, CRLF
	};

	/**
	 * Get current line ending mode. It is auto-detected from the
	 * buffer contents.
	 */
	virtual Type get() = 0;

	/**
	 * @mode: Line mode to set.
	 *
	 * Set the line ending mode to the given @mode. Existing line end
	 * characters in the buffer are not touched. Only the newly added
	 * texts will have @mode line end characters.
	 */
	virtual void set(Type mode) = 0;

	/**
	 * @mode: Line mode to convert.
	 *
	 * Set the line ending mode to the given @mode and convert all line end
	 * characters in the buffer to @mode line end characters.
	 */
	virtual void convert(Type mode) = 0;

	/**
	 * Convert EOL characters to majority of line mode. This is helpful
	 * when the buffer contains mixed line modes and we want to fix it.
	 */
	virtual void fix() = 0;
};
/**
 * @title: IEditorSearch
 * @short_description: Text editor search interface
 */

class IEditorSearch {
public:
	// default virtual destructor
	virtual ~IEditorSearch() {
	}

	/**
	 * @search: String to search for
	 * @start: Where to search from
	 * @end: Where to stop searching
	 * @result_start: Will be set to the start of the search_result (or NULL)
	 * @result_end: Will be set to the end of the search_result (or NULL)
	 *
	 * Search forward from start to end
	 *
	 */
	virtual gboolean
			forward(const gchar* search, gboolean case_sensitive,
					IEditorCell* start, IEditorCell* end,
					IEditorCell** result_start, IEditorCell** result_end) = 0;

	/**
	 * @search: String to search for
	 * @start: Where to search from
	 * @end: Where to stop searching
	 * @result_start: Will be set to the start of the search_result (or NULL)
	 * @result_end: Will be set to the end of the search_result (or NULL)
	 *
	 * Search backward from end to start
	 */

	virtual gboolean
			backward(const gchar* search, gboolean case_sensitive,
					IEditorCell* start, IEditorCell* end,
					IEditorCell** result_start, IEditorCell** result_end) = 0;
};
/**
 * @title: IEditorSelection
 * @short_description: Text editor selection interface
 */

class IEditorSelection {
public:
	// default virtual destructor
	virtual ~IEditorSelection() {
	}

	/**
	 * Returns TRUE if editor has any text selected. The selection
	 * positions can be retrieved with editor_selection_get_start()
	 * and editor_selection_get_end().
	 *
	 * Returns: TRUE if there is text selected else FALSE.
	 */
	virtual gboolean has_selection() = 0;

	/**
	 * Gets curerntly selected text in editor.
	 *
	 * Returns: A newly allocated buffer of currently selected characters.
	 * NULL if there is no selection. The returned buffer must be freed after
	 * use.
	 */
	virtual gchar* get() = 0;

	/**
	 * @start: Begin of selection
	 * @end: End of selection
	 * @scroll: Scroll selection onscreen
	 *
	 * Select characters between start and end. Start and end don't have to
	 * be ordered.
	 */
	virtual void set(Iterable* start, Iterable* end, gboolean scroll) = 0;

	/**
	 * Gets start position of selection text.
	 *
	 * Return: Start of selection or NULL if there is no selection.
	 */
	virtual Iterable* get_start() = 0;

	/**
	 * Get end position of selection. If there is no selection, returns
	 * NULL.
	 *
	 * Returns: End of selection or NULL if there is no selection.
	 */
	virtual Iterable* get_end() = 0;

	/**
	 * @err: Error propagation and reporting
	 *
	 * Selects current block of code. The definition of block of code
	 * depends on highlight mode used (programming language). Some
	 * highlight mode does not have block concept, in that case this
	 * method does not do anything.
	 */
	virtual void select_block() = 0;

	/**
	 * Select current function block. The definition of function block
	 * depends on highlight mode used (programming language). Some
	 * highlight mode does not have function concept, in that case this
	 * method does not do anything.
	 */
	virtual void select_function() = 0;

	/**
	 * Select whole buffer.
	 */
	virtual void select_all() = 0;

	/**
	 * @text: Replacement text.
	 * @length: Length of the text to used in @text.
	 *
	 * Replaces currently selected text with the @text. Only @length amount
	 * of characters are used from @text buffer to replace.
	 */
	virtual void replace(const gchar *text, gint length) = 0;
};
/**
 * @title: IEditorTip
 * @short_description: Editor call tips assistance framework
 */

class IEditorTip {
public:
	// default virtual destructor
	virtual ~IEditorTip() {
	}

	/**
	 * @tips: list of alternative tips.
	 * @position: Tip position.
	 *
	 * Show tips showing more information on current context. No user feedback
	 * is required when tips are shown. @position indicates
	 * the position before which is the known context and after which are
	 * the suggestions. Usually the editor would use this to
	 * align the choices displayed such that the carat is just at this
	 * position when the choices are displayed.
	 *
	 */
	virtual void show(std::list<const gchar*> tips, Iterable *position) = 0;

	/**
	 * Cancels the last shown tooltip
	 */
	virtual void cancel() = 0;

	/**
	 * Returns: whether a tooltip is crrently shown
	 */
	virtual gboolean visible() = 0;
};
/**
 * @title: IEditorView
 * @short_description: Text editor view interface
 *
 * An editor view is a visual representation of the editor. An editor
 * can have multiple views. All views of an editor show the same editor
 * content (buffer). Consequently, any change done in one view is
 * updated in all other views.
 */

class IEditorView {
public:
	virtual ~IEditorView() {
	}
	/**
	 * Creates a new view for the editor. The newly created view gets
	 * the user focus and scrolls to the same location as last view.
	 */
	virtual void create() = 0;

	/**
	 * Removes currently focused editor view. It does not remove the
	 * last view of the editor. That is, if currently there is only
	 * one view of the editor, this function does nothing.
	 */
	virtual void remove_current() = 0;

	/**
	 * Total number of views currently present. It will never be less
	 * than 1. Invalid return values are considered error condition.
	 */
	virtual gint get_count() = 0;
};
/**
 * @title: IEditorZoom
 * @short_description: Text editor zoom interface
 */
class IEditorZoom {
public:
	// default virtual destructor
	virtual ~IEditorZoom() {
	}
	/**
	 * Zoom in
	 */
	virtual void in() = 0;

	/**
	 * Zoom out
	 */
	virtual void out() = 0;
};

}
;

#endif

