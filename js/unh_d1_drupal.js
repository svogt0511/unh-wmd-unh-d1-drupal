// General javascript needed by the d1pdt module.

// 'Back to top' button behavior on course-search-results pages
(function ($) {
  Drupal.behaviors.unh_d1_drupal = {
    attach: function (context, settings) {

      // Implements the 'back to top' button on course-search-results pages.
      $(window).scroll(function () {
          if ($(this).scrollTop() > 150) {
              $('#back-to-top').fadeIn();
          } else {
              $('#back-to-top').fadeOut();
          }
      });
      // scroll body to 0px on click
      $('#back-to-top').click(function () {
          $('#back-to-top').tooltip('hide');
          $('body,html').animate({
              scrollTop: 0
          }, 800);
          return false;
      });

      // This should be recoded to be only attached to a course-search page.
      // We are having to test for the functions because we get errors in the admin
      // interface because the functions do not exist and cause anomalies (like no
      // admin menu bar).
      if ($.isFunction($('.course-search-page #demo.collapse').collapse)) {
        $('.course-search-page #demo.collapse').collapse("show");
      }
      if ($.isFunction($('.course-search-page .choose-topics-btn').toggleClass)) {
        $('.course-search-page .choose-topics-btn').toggleClass("collapsed");
      }

      // Bootstrap accordion for right rail sections does not seem to alter
      // '+' or '-' properly so we add this code.
      $(".course-page .card .card-header a[data-toggle='collapse']").click(function(e){
        $(this).find('.fa').toggle();
      });
    }
  };

  //
  // @todo: find out why above doesn't seem to get loaded properly.
  //
  function removeQueryStringParameter(key, url) {
    if (!url || !key) {
      return '';
    }

    var hashParts = url.split('#');

    var regex = new RegExp("([?&])" + key + "=.*?(&|#|$)", "i");

    if (hashParts[0].match(regex)) {
        //REMOVE KEY AND VALUE
        url = hashParts[0].replace(regex, '$1');

        //REMOVE TRAILING ? OR &
        url = url.replace(/([?&])$/, '');

        //ADD HASH
        if (typeof hashParts[1] !== 'undefined' && hashParts[1] !== null)
            url += '#' + hashParts[1];
    }

    return url;
  }

  // Bootstrap accordion for right rail sections does not seem to alter
  // '+' or '-' properly so we add this code.
  $(".course-page .card .card-header a[data-toggle='collapse']").click(function(e){
    $(this).find('.fa').toggle();
  });

}(jQuery));





