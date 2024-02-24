#include "script.h"
namespace loopxia
{
    class GameObject : ScriptableObject
    {

        // transform of object
        private Transform _transform;

        // hierarchy parenting
        private GameObject _parent;
        public GameObject()
        {
        }

        public Vector3 Position() { return _transform.Position(); }
    }
}
