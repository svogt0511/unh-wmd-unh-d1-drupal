// Course node title autocomplete - queries D1 to match course titles.  Fills in course code
// field based on title selected by the user to set the unique relationship between the
// Drupal course node and the D1 course.

// Use attach to attach behaviors to this module.
(function ($) {
  Drupal.behaviors.autocompleteSupervisor = {
    attach: function (context, settings) {      
      // Autocomplete for course node edit form - course title.
      // Used in combination with the php callback that builds the list of courses
      // available from D1.  The user does not need to choose from the list.
      //
      // ** See the module hook_menu for the autocomplete callback.
      $("form.node-course-form input#edit-title", context).bind('autocompleteSelect', function(event, node) {
        courseCode = $(node).data('autocompleteValue');
        courseTitle = $(node).text();

        // Remove the '(code)' from the title string.
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

      // Autocomplete for course node edit form - certificate title.
      // Used in combination with the php callback that builds the list of certificates
      // available from D1.  The user does not need to choose from the list.
      //
      // ** See the module hook_menu for the autocomplete callback.
      // certificate autocomplete
      $('input[id*="field-certificate-title"][id^="edit-field-certificate"]' , context).bind('autocompleteSelect', function(event, node) {
        certificateCode = $(node).data('autocompleteValue');
        certificateTitle = $(node).text();
        
        // Remove the '(code)' from the title string.
        part_to_remove = '(' + certificateCode + ')';
        certificateTitle_slice = certificateTitle.slice(-part_to_remove.length);
        if (certificateTitle_slice === part_to_remove) {
          certificateTitle = certificateTitle.substring(0, certificateTitle.length - (part_to_remove.length + 1));
          certificateTitle = certificateTitle.trim();
        }

        parent_this = $(this).closest('div[class*="field-name-field-certificate-title"]');
        sibling_this = $(parent_this).next('div[class*="field-name-field-certificate-code"]');
        child_this = $(sibling_this).find('input[id*="field-certificate-code"]');

        $(child_this).val(certificateCode);
        $(this).val(certificateTitle);
        $('div[class="dropdown"]').hide();

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
      
      $('form.node-course-form input[id*="field-certificate-title"]' ).keydown(

        function() {
            parent_this = $(this).closest('div[class*="field-name-field-certificate-title"]');
            sibling_this = $(parent_this).next('div[class*="field-name-field-certificate-code"]');
            child_this = $(sibling_this).find('input[id*="field-certificate-code"]');
            $(child_this).val('');
        }
      );
     
    }
  };


})(jQuery);
