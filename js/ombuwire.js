(function ($) {

$(function() {

  if ($('#ombuwire-sidebar:not(.processed)').length == 0) {
    return;
  }

  var $sidebar = $('#ombuwire-sidebar'),
      $cloak = $('.cloak', $sidebar),
      $opener = $('.opener', $sidebar),
      $closer = $('.closer', $sidebar),
      fullWidth;

  // move the sidebar far off screen so we can measure its full width
  $sidebar.css({left: '-999px'});
  $cloak.css({display: 'block'});
  fullWidth = $sidebar.width();

  // pull the sidebar just off the screen to the left
  $sidebar.css({left: '-'+fullWidth+'px'});


  // open/close click handlers
  function open(e) {
    if (e) { e.preventDefault(); }
    $sidebar.animate({left: '0px'}, {duration: 'fast'});
    $opener.fadeOut('fast');
    $.cookie('ombuwire.open', 1);
  }

  function close(e) {
    if (e) { e.preventDefault(); }
    $sidebar.animate({left: '-'+fullWidth+'px'}, {duration: 'fast'});
    $opener.fadeIn('fast');
    $.cookie('ombuwire.open', 0);
  }


  // bind handlers
  $opener.click((function() {
    return open;
  })());

  $closer.click((function() {
    return close;
  })());


  // Initial state
  if ($.cookie('ombuwire.open') == 1) {
    $sidebar.css({left: '0px'});
    $opener.hide();
  }


  $sidebar.addClass('processed');


  $('a.noclick').click(function(e) {
    e.preventDefault();
    return false;
  });
});

})(jQuery);