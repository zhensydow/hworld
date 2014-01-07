dtime = 0

function start()
   terminal.newLine( 'Start state' )
end

function update( dt )
   dtime = dtime + dt
   --print( 'Update state ' .. dt .. ' and ' .. dtime )
   if dtime > 1 then
      engine.newState( 'test2' )
      dtime = 0
   end
end

function stop()
   terminal.newLine( 'Stop state' )
end
