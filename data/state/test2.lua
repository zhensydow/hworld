function start()
   print( 'Start state test2' )
end

function update( dt )
   print( 'Update state ' .. dt .. ' test2' )
   if input.isKeyPressed( input.K )then
      engine.newstate( 'test' )
   end
end

function stop()
   print( 'Stop state test2' )
end
