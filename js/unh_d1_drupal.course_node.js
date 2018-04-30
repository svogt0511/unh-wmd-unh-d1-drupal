// Course node title autocomplete - queries D1 to match course titles.  Fills in course code
// field based on title selected by the user to set the unique relationship between the
// Drupal course node and the D1 course.

// Use attach to attach behaviors to this module.
(function ($) {
  Drupal.behaviors.autocompleteSupervisor = {
    attach: function (context, settings) {      
      // Autocomplete for course node edit form.
      // Used in combination with the php callback that builds the list of courses
      // available from D1.  The user does not need to choose from the list.
      $("form.node-course-form input#edit-title", context).bind('autocompleteSelect', function(event, node) {
        courseCode = $(node).data('autocompleteValue');
        courseTitle = $(node).text();
        
        // Remove the '(coursecode)' from the title string.
        part_to_remove = '(' + courseCode + ')';
        courseTitle_slice = courseTitle.slice(-part_to_remove.length);
        if (courseTitle_slice === part_to_remove) {
          courseTitle = courseTitle.substring(0, courseTitle.length - (part_to_remove.length + 1));
          courseTitle = courseTitle.trim();
        }

        // Set the form properties.
        $("form.node-course-form input#edit-title").val(courseTitle); 
        $("form.node-course-form input#edit-field-course-code-und-0-value").val(courseCode);
      });
    }
  };
  
  Drupal.behaviors.unh_d1_drupal = {
    attach: function (context, settings) { 
      // Clear the course code the minute the user strikes a key in the title field, 
      // otherwise, we could end up with inconsistent title/course code.
      $( "form.node-course-form input#edit-title" ).keydown(
        function() {
          $("form.node-course-form input#edit-field-course-code-und-0-value").val('');
        }
      );     
    }
  };


})(jQuery);
