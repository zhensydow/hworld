count = 0

function start()
   print( 'Start state' )
end

function update( dt )
   count = count + 1
   print( 'Update state ' .. dt .. ' and ' .. count )
   if count > 10 then
      engine.newstate( 'test2' )
      count = 0
   end
end

function stop()
   print( 'Stop state' )
end
