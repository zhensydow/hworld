function start()
   terminal.newLine( 'Start state test2' )
end

function update( dt )
   --print( 'Update state ' .. dt .. ' test2' )
   if input.isKeyPressed( input.K )then
      engine.newstate( 'test' )
   end
   if input.isButtonPressed( input.MouseLeft )then
      print( "MOUSED" )
   end
end

function stop()
   terminal.newLine( 'Stop state test2' )
end
