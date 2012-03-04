(function($) {
  Drupal.behaviors.noty_messages = {
    attach: function(context) {
    //butt click fxn
    $('.test-noty-messages').click(function(event){
      event.preventDefault();
      event.stopPropagation();
      //get name
      var name = $(this).attr('name');
      // get current actives
      if (name == 'global' || $('#edit-noty-messages-global-is-noty-' + name).is(':checked')){
        // change settings
        var notySettings = Drupal.settings.notyMessages;
        notySettings.notyType[name] = $('#edit-noty-messages-' + name + '-type :selected').val();
        notySettings.notyLayout[name] = $('#edit-noty-messages-' + name + '-layout :selected').val();
        notySettings.notyTextAlign[name] = $('#edit-noty-messages-' + name + '-text-align :selected').val();
        notySettings.notySpeed[name] = $('#edit-noty-messages-' + name + '-speed').val();
        notySettings.notyTimeout[name] = $('#edit-noty-messages-' + name + '-timeout').val();
        notySettings.notyClosable[name] = $('#edit-noty-messages-' + name + '-closable').is(':checked');
        notySettings.notyClickClose[name] = $('#edit-noty-messages-' + name + '-click-close').is(':checked');
        notySettings.notyModal[name] = $('#edit-noty-messages-' + name + '-modal').is(':checked');
        console.log(notySettings);
        testMessages = new Array('This is a ' + name + ' message', 'And this is another one!');
        new notyMessages.renderType(name, testMessages, notySettings);
      }
      else{
        alert('This is not a noty message');
      }
      //if (name != 'global' && )
      //for (setting in Drupal.settings.notyMessages){

      //}
      return false;
    });
    }
  }
})(jQuery);